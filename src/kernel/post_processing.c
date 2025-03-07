/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "post_processing.h"
#include "util/pos.h"
#include "util/util.h"
#include <X11/Xutil.h>
#include <kernel/color.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <util/math.h>

/* Runs function over each pixel in a sub-view */
static inline void	filter(
	const t_img *img,
	float *buffers[2],
	int size,
	float (*f)(float *, size_t, t_pos))
{
	t_pos			pos;

	pos = (t_pos){0, 0};
	while (pos.y < img->height)
	{
		buffers[1][pos.x + pos.y * img->width] = 0;
		if (pos.y >= size / 2 && pos.y <= img->height - size / 2
			&& pos.x >= size / 2 && pos.x <= img->width - size / 2)
			buffers[1][pos.x + pos.y * img->width]
				= f(buffers[0], img->width, pos);
		++pos.x;
		if (pos.x != img->width)
			continue ;
		pos.x = 0;
		++pos.y;
	}
}

float	*postprocess_edge_filter(
	t_img *img,
	float *in)
{
	const size_t	pixel_size = img->width * img->height;
	size_t			i;
	t_color			color;

	i = 0;
	while (i < pixel_size)
	{
		color = ((t_color *)img->data)[i];
		in[i++] = (0.30f * color.channels.r + 0.59f * color.channels.g
				+ 0.11f * color.channels.b) / 255.0f;
	}
	filter(img, (float *[2]){in, in + pixel_size}, 3, postprocess_sobel);
	filter(img, (float *[2]){in + pixel_size, in}, 5, postprocess_gauss_blur_5);
	return (in);
}

static inline t_color get_pixel_clamped(const t_color *buffer, t_pos size, int x, int y) {
    if (x < 0) x = 0; if (x >= size.x) x = size.x - 1;
    if (y < 0) y = 0; if (y >= size.y) y = size.y - 1;
    return buffer[y * size.x + x];
}

static inline float cubic_weight(float x) {
	if (x <= 1) {
		return 1 - (-0.5 + 3) * x * x + (-0.5 + 2) * x * x * x;
	} else if (x < 2) {
		return -4 * -0.5 + 8 * -0.5 * x - 5 * -0.5 * x * x + -0.5 * x * x * x;
	}
	return 0.0;
}
void CalcCoeff4x4(float x, float y, float *coeff) {

	float u = x - floor(x);
	float v = y - floor(y);

	u += 1;
	v += 1;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			coeff[i * 4 + j] =
				cubic_weight(fabs(u - i)) * cubic_weight(fabs(v - j));
		}
	}
}

static inline t_color color_blend(const t_color *c, const float *w) {
    float sum_r = 0, sum_g = 0, sum_b = 0, sum_w = 0;
    for (int i = 0; i < 16; ++i) {
        sum_w += w[i];
        sum_b += c[i].channels.b * w[i];
        sum_g += c[i].channels.g * w[i];
        sum_r += c[i].channels.r * w[i];
    }
    if (sum_w > 0) {
        sum_b /= sum_w;
        sum_g /= sum_w;
        sum_r /= sum_w;
    }
    return (t_color){ .channels = {
		.b = sum_b,
		.g = sum_g,
		.r = sum_r,
		.a = 0,
	}};
}

float cubic_hermite(float A, float B, float C, float D, float t) {

   float a = -A / 2.0f + (3.0f*B) / 2.0f - (3.0f*C) / 2.0f + D / 2.0f;
   float b = A - (5.0f*B) / 2.0f + 2.0f*C - D / 2.0f;
   float c = -A / 2.0f + C / 2.0f;
   float d = B;

   return a*t*t*t + b*t*t + c*t + d;
}

t_color bicubic_interpolate(const t_color *buffer, t_pos size, t_vec2d z) {
	t_color out;
    t_color c[16];
    float weights[16];

    for (int j = -1; j <= 2; ++j) {
        for (int i = -1; i <= 2; ++i) {
            c[(j + 1) * 4 + (i + 1)] = get_pixel_clamped(buffer, size, (int)z.x + i, (int)z.y + j);

        }
    }
	out = (t_color){0};
	for (int i = 0; i < 4; i++) {
		const float xfract = z.x - floor(z.x);
		const float yfract = z.y - floor(z.y);
		const uint8_t *p = (uint8_t *)c;
		float col0 = cubic_hermite(p[4*(0+0*4) + i], p[4*(1+0*4) + i], p[4*(2+0*4) + i], p[4*(3+0*4) + i], xfract);
		float col1 = cubic_hermite(p[4*(0+1*4) + i], p[4*(1+1*4) + i], p[4*(2+1*4) + i], p[4*(3+1*4) + i], xfract);
		float col2 = cubic_hermite(p[4*(0+2*4) + i], p[4*(1+2*4) + i], p[4*(2+2*4) + i], p[4*(3+2*4) + i], xfract);
		float col3 = cubic_hermite(p[4*(0+3*4) + i], p[4*(1+3*4) + i], p[4*(2+3*4) + i], p[4*(3+3*4) + i], xfract);

		float value = cubic_hermite(col0, col1, col2, col3, yfract);

		((uint8_t *)&out)[i] = fmin(fmax(value, 0.0f), 255.0f);
	}
    return (out);
}

void	postprocess_upscale(t_img *img, t_pos size, t_color *in)
{
	const size_t	pixel_size = img->width * img->height;
	size_t			i;
	const t_color			*data = (const t_color *)img->data;

	t_pos pos;
	pos.y = 0;

	while (pos.y < img->height)
	{
		pos.x = 0;
		while (pos.x < img->width)
		{
			t_vec2d z = (t_vec2d){(pos.x + 0.5) / (float)img->width * size.x - 0.5, (pos.y + 0.5) / (float)img->height * size.y - 0.5};
			in[pos.x + pos.y * img->width] = bicubic_interpolate(data, size, z);
			++pos.x;
		}
		++pos.y;
	}
	ft_memcpy(img->data, in, pixel_size * sizeof(t_color));
}
