#include "post_processing.h"
#include <kernel/color.h>
#include <stdio.h>
#include <util/math.h>

static inline t_vec2f	convolve(const float *in, size_t line_length, t_pos pos)
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
			r.x += sobel_x[1 + offset.x + (1 + offset.y) * 3] * in[(pos.x + offset.x) + (pos.y + offset.y) * line_length];
			r.y += sobel_y[1 + offset.x + (1 + offset.y) * 3] * in[(pos.x + offset.x) + (pos.y + offset.y) * line_length];
			++offset.x;
		}
		++offset.y;
	}
	return (r);
}

static inline float	blur(const float *in, size_t line_length, t_pos pos)
{
	static const float	blur[] = {0.01, 0.08, 0.01, 0.08, 0.64, 0.08, 0.01, 0.08, 0.01};
	float				r;
	t_pos				offset;


	r = 0;
	offset.y = -1;
	while (offset.y <= 1)
	{
		offset.x = -1;
		while (offset.x <= 1)
		{
			r += blur[1 + offset.x + (1 + offset.y) * 3] * in[(pos.x + offset.x) + (pos.y + offset.y) * line_length];
			++offset.x;
		}
		++offset.y;
	}
	return (r);
}

float	*sobel(t_img *img, float *buffer)
{
	const size_t	size = img->width * img->height;
	size_t			i;
	t_color			color;
	t_color			*data = (t_color *)img->data;

	// To black and white
	i = 0;
	while (i < size)
	{
		color = data[i];
		buffer[i++] = (0.30f * color.channels.r + 0.59f * color.channels.g + 0.11f * color.channels.b) / 255.0f;
	}

	// Apply sobel
	for (int y = 0; y < img->height; ++y)
	{
		for (int x = 0; x < img->width; ++x)
		{
			buffer[x + y * img->width + size] = 1;
			if (y == 0 || y + 2 == img->height || x == 0 || x + 2 == img->width)
				continue ;
			t_vec2f d = convolve(buffer, img->width, (t_pos){x, y});
			buffer[x + y * img->width + size] = sqrt(d.x * d.x + d.y * d.y);
		}
	}
	
	// Blur
	for (int y = 0; y < img->height; ++y)
	{
		for (int x = 0; x < img->width; ++x)
		{
			buffer[x + y * img->width + size] = 1;
			if (y == 0 || y + 2 == img->height || x == 0 || x + 2 == img->width)
				continue ;
			buffer[x + y * img->width] = blur(buffer + size, img->width, (t_pos){x, y});
		}
	}
	return (buffer);
}
