/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_processing_interpolation.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "kernel/color.h"
#include "post_processing.h"
#include "util/vector.h"
#include <math.h>

static inline t_color
	get_pixel_clamped(const t_color *buffer, t_pos size, int x, int y)
{
	if (x < 0)
		x = 0;
	else if (x >= size.x)
		x = size.x - 1;
	if (y < 0)
		y = 0;
	if (y >= size.y)
		y = size.y - 1;
	return (buffer[y * size.x + x]);
}

static inline float
	cubic_hermite(float cols[4], float t)
{
	const float	w[4] = {
		-cols[0] / 2.0f + (3.0f * cols[1]) / 2.0f
		- (3.0f * cols[2]) / 2.0f + cols[3] / 2.0f,
		cols[0] - (5.0f * cols[1]) / 2.0f + 2.0f * cols[2] - cols[3] / 2.0f,
		-cols[0] / 2.0f + cols[2] / 2.0f,
		cols[1]};

	return (w[0] * t * t * t + w[1] * t * t + w[2] * t + w[3]);
}

static inline void
	sample_pixels(const t_color *in, t_pos size, t_color *pixels, t_pos center)
{
	t_pos	pos;

	pos.y = -1;
	while (pos.y <= 2)
	{
		pos.x = -1;
		while (pos.x <= 2)
		{
			pixels[(pos.y + 1) * 4 + (pos.x + 1)] = get_pixel_clamped(in,
					size, center.x + pos.x, center.y + pos.y);
			++pos.x;
		}
		++pos.y;
	}
}

static inline t_color
	bicubic_interpolate(const t_color *buffer, t_pos size, t_vec2d z)
{
	const float		xfract = z.x - floor(z.x);
	const uint8_t	p[16 * sizeof(t_color)];
	t_color			out;
	int				i;

	sample_pixels(buffer, size, (t_color *)p, (t_pos){z.x, z.y});
	out = (t_color){0};
	i = 0;
	while (i < 4)
	{
		((uint8_t *)&out)[i] = fmin(fmax(cubic_hermite((float [4]){
			cubic_hermite((float [4]){p[4*(0+0*4) + i], p[4*(1+0*4) + i],
					p[4*(2+0*4) + i], p[4*(3+0*4) + i]}, xfract),
			cubic_hermite((float [4]){p[4*(0+1*4) + i], p[4*(1+1*4) + i],
					p[4*(2+1*4) + i], p[4*(3+1*4) + i]}, xfract),
			cubic_hermite((float [4]){p[4*(0+2*4) + i], p[4*(1+2*4) + i],
					p[4*(2+2*4) + i], p[4*(3+2*4) + i]}, xfract),
			cubic_hermite((float [4]){p[4*(0+3*4) + i], p[4*(1+3*4) + i],
					p[4*(2+3*4) + i], p[4*(3+3*4) + i]}, xfract),
		}, z.y - floor(z.y)), 0.f), 255.f);
		++i;
	}
	return (out);
}

#define __EXPAND(...) __VA_ARGS__
#define EXPAND(...) __EXPAND(__VA_ARGS__)
#define OMP_KERNEL(__a, __b, __i, __size, __s) \
_Pragma(__a) \
{ \
	_Pragma(__b) \
	for (__i = 0; (__i) < (__size); ++(__i)) \
	{ __s } \
}

void	postprocess_bicubic(
	const t_color *in,
	t_pos in_size,
	t_color *out,
	t_pos out_size)
{
	int	i;

	i = 0;
	OMP_KERNEL("omp shared(out)", "omp for private(i)",
		i, out_size.x * out_size.y, {
		out[i] = bicubic_interpolate(in, in_size, (t_vec2d){
			((i % out_size.x) + 0.5) / (float)out_size.x * in_size.x - 0.5,
			((i / (float)out_size.x) + 0.5)
			/ (float)out_size.y * in_size.y - 0.5});
	});
}

void	postprocess_bilinear(
	const t_color *in,
	t_pos in_size,
	t_color *out,
	t_pos out_size)
{
	int		i;
	t_vec2d	pos;

	OMP_KERNEL("omp shared(out)", "omp for private(i, pos)",
		i, out_size.x * out_size.y, EXPAND({
		pos = (t_vec2d){((i % out_size.x) + 0.5)
			/ (float)out_size.x * in_size.x - 0.5,
			((i / (float)out_size.x) + 0.5)
			/ (float)out_size.y * in_size.y - 0.5};
		out[i] = color_lerp(
				color_lerp(
					get_pixel_clamped(in, in_size, pos.x, pos.y),
					get_pixel_clamped(in, in_size, pos.x + 1, pos.y),
					fmod(pos.x, 1.0)),
				color_lerp(
					get_pixel_clamped(in, in_size, pos.x, pos.y + 1),
					get_pixel_clamped(in, in_size, pos.x + 1, pos.y + 1),
					fmod(pos.x, 1.0)),
				fmod(pos.y, 1.0)
				);
	}));
}
