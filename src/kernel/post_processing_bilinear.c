/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_processing_bilinear.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Bulinear image filtering
 */

#include <kernel/post_processing.h>
#include <util/math.h>

/* Gets a clamped pixel value */
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

void	postprocess_bilinear(
	const t_color *in,
	t_pos in_size,
	t_color *out,
	t_pos out_size)
{
	int		i;
	t_vec2d	pos;

	FRACTOL_OMP("omp parallel for shared(in, out) private(i, pos)",
		i, out_size.x * out_size.y, FRACTOL_EXPAND({
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
