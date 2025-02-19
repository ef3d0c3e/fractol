/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "image.h"
#include "mlx_int.h"

inline void	image_pixel(t_img *img, t_pos pos, t_color color)
{
	((t_color *)img->data)[pos.x + pos.y * img->width] = color;
}

void	image_fill(t_img *img, t_color color)
{
	t_pos	pos;

	pos.y = 0;
	while (pos.y < img->height)
	{
		pos.x = 0;
		while (pos.x < img->width)
		{
			image_pixel(img, pos, color);
			++pos.x;
		}
		++pos.y;
	}
}
