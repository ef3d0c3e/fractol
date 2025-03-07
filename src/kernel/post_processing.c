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
#include "util/util.h"

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

void	postprocess_upscale(t_img *img, t_pos size, t_color *in)
{
	const t_color			*data = (const t_color *)img->data;

	postprocess_bicubic(data, size, in, (t_pos){img->width, img->height});
	ft_memcpy(img->data, in, (img->width * img->height) * sizeof(t_color));
}
