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
			r += gauss5[2 + offset.x + (2 + offset.y) * 5] * in[(pos.x + offset.x) + (pos.y + offset.y) * line_length];
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
			buffer[x + y * img->width + size] = 0;
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
			buffer[x + y * img->width] = 0;
			if (y <= 1 || y + 3 == img->height || x <= 1 || x + 3 == img->width)
				continue ;
			buffer[x + y * img->width] = blur(buffer + size, img->width, (t_pos){x, y});
		}
	}

	// Blur
	for (int y = 0; y < img->height; ++y)
	{
		for (int x = 0; x < img->width; ++x)
		{
			if (y <= 1 || y + 3 == img->height || x <= 1 || x + 3 == img->width)
				continue ;
			buffer[x + y * img->width + size] = blur(buffer, img->width, (t_pos){x, y});
		}
	}

	return (buffer + size);
}
