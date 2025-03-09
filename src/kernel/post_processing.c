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

/**
 * @brief Post processing for downsampling/upsampling
 */

#include <kernel/post_processing.h>
#include <kernel/color.h>
#include <util/util.h>
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

/* Propagate dense areas */
static inline float	propagate(
	float *in,
	size_t line_length,
	t_pos pos)
{
	static const float	weights[] = {
		0.1, 0.2, 0.2, 0.2, 0.1,
		0.2, 0.4, 0.5, 0.4, 0.2,
		0.2, 0.5, 1.0, 0.5, 0.2,
		0.2, 0.4, 0.5, 0.4, 0.2,
		0.1, 0.2, 0.2, 0.2, 0.1,
	};
	float				r;
	t_pos				offset;

	r = 0;
	offset.y = -2;
	while (offset.y <= 2)
	{
		offset.x = -2;
		while (offset.x <= 2)
		{
			r += weights[2 + offset.x + (2 + offset.y) * 5]
				* in[(pos.x + offset.x) + (pos.y + offset.y) * line_length];
			++offset.x;
		}
		++offset.y;
	}
	return (r);
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
	filter(img, (float *[2]){in, in + pixel_size}, 5, postprocess_gauss_blur_5);
	return (in + pixel_size);
}

float	*postprocess_upscale(t_img *img, t_pos size, float *in)
{
	const size_t	pixel_size = img->width * img->height;
	const t_color	*data = (const t_color *)img->data;
	t_color			color;
	size_t			i;

	postprocess_bilinear(data, size, (t_color *)in,
		(t_pos){img->width, img->height});
	ft_memcpy(img->data, in, (img->width * img->height) * sizeof(t_color));
	i = 0;
	while (i < pixel_size)
	{
		color = ((t_color *)img->data)[i];
		in[i++] = (0.30f * color.channels.r
				+ 0.59f * color.channels.g + 0.11f * color.channels.b) / 255.0f;
	}
	filter(img, (float *[2]){in, in + pixel_size}, 3, postprocess_sobel);
	filter(img, (float *[2]){in + pixel_size, in}, 5, propagate);
	i = 0;
	while (i < pixel_size)
	{
		((float *)in)[i] = fmax(fminf(log(((float *)in)[i]) - size.x
					/ (double)img->width, 0.f), -10.f);
		++i;
	}
	return ((float *)in);
}
