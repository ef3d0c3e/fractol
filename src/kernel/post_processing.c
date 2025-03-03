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
#include <kernel/color.h>
#include <stdio.h>
#include <util/math.h>

/* Uses Sobel edge detection algorithm */
static inline float	sobel_filter(
	float *in,
	int line_length,
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

/* Performs 5x5 gaussian blur over a float matrix */
static inline float	gauss_blur_5x5(
	float *in,
	int line_length,
	t_pos pos)
{
	static const float	gauss5[] = {0.00296902, 0.01330621, 0.02193823,
		0.01330621, 0.00296902, 0.01330621, 0.0596343, 0.09832033, 0.0596343,
		0.01330621, 0.02193823, 0.09832033, 0.16210282, 0.09832033, 0.02193823,
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

/* Runs function over each pixel in a sub-view */
static inline void	filter(
	const t_img *img,
	float *buffers[2],
	int size,
	float (*f)(float *, int, t_pos))
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
	float *buffer)
{
	const size_t	size = img->width * img->height;
	size_t			i;
	t_color			color;

	i = 0;
	while (i < size)
	{
		color = ((t_color *)img->data)[i];
		buffer[i++] = (0.30f * color.channels.r + 0.59f * color.channels.g
				+ 0.11f * color.channels.b) / 255.0f;
	}
	filter(img, (float *[2]){buffer, buffer + size}, 3, sobel_filter);
	filter(img, (float *[2]){buffer + size, buffer}, 5, gauss_blur_5x5);
	return (buffer);
}
