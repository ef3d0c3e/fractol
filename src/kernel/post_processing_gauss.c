/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_processing_gauss.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file 5x5 gauss kernel
 */

#include <kernel/post_processing.h>

inline float	postprocess_gauss_blur_5(
	float *in,
	size_t line_length,
	t_pos pos)
{
	static const float	gauss5[] = {0.00296902, 0.01330621, 0.02193823,
		0.01330621, 0.00296902, 0.01330621, 0.0596343, 0.09832033, 0.0596343,
		0.01330621, 0.02193823, 0.09832033, 0.26210282, 0.09832033, 0.02193823,
		0.01330621, 0.0596343, 0.09832033, 0.0596343, 0.01330621, 0.00296902,
		0.01330621, 0.02193823, 0.01330621, 0.00296902};
	float				r;
	t_pos				offset;

	r = 0;
	offset.y = -2;
	while (offset.y <= 2)
	{
		offset.x = -2;
		while (offset.x <= 2)
		{
			r += gauss5[2 + offset.x + (2 + offset.y) * 5]
				* in[(pos.x + offset.x) + (pos.y + offset.y) * line_length];
			++offset.x;
		}
		++offset.y;
	}
	return (r);
}
