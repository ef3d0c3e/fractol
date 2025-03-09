/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_processing_sobel.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Sobel kernel
 */

#include <kernel/post_processing.h>
#include <util/math.h>

inline float	postprocess_sobel(
	float *in,
	size_t line_length,
	t_pos pos)
{
	static const float	sobel_x[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
	static const float	sobel_y[] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
	t_vec2f				r;
	t_pos				offset;

	r = (t_vec2f){0.f, 0.f};
	offset.y = -1;
	while (offset.y <= 1)
	{
		offset.x = -1;
		while (offset.x <= 1)
		{
			r.x += sobel_x[1 + offset.x + (1 + offset.y) * 3]
				* in[(pos.x + offset.x) + (pos.y + offset.y) * line_length];
			r.y += sobel_y[1 + offset.x + (1 + offset.y) * 3]
				* in[(pos.x + offset.x) + (pos.y + offset.y) * line_length];
			++offset.x;
		}
		++offset.y;
	}
	return (sqrt(r.x * r.x + r.y * r.y));
}
