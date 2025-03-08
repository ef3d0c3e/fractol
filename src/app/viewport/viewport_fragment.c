/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_fragment.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "kernel/color.h"
#include "util/vector.h"
#include "viewport.h"
#include <complex.h>
#include <math.h>
#include <stdio.h>

/**
 * @brief Gets the weight of a sample
 *
 * This function returns an approximation of:
 *  \f$\frac{\exp(-\frac{1}{2} (x^2 + y^2))}
 *  {\int_{-size}^{+size} \exp(-t^2) \mathtt dt}\f$
 * */
static inline float	gauss_sample_weight(size_t size, int x, int y)
{
	static const float	kernel_sums[] = {[3] = 4.897640403536304,
	[5] = 6.168924081028881, [7] = 6.2797847959347015, [9] = 6.283147856202572,
	[11] = 6.283185221483608, [13] = 6.2831853741872, [15] = 6.283185374416782};

	if (size <= 15)
		return (expf(-(x * x + y * y) / 2.f) / kernel_sums[size]);
	return (expf(-(x * x + y * y) / 2.f) / kernel_sums[15]);
}

static void	
	fragment_oversample(
		struct s_fragment_data *data,
		t_color (*shader)(double _Complex z, void *data),
		void *closure)
{
	const size_t	size = data->render_size.x * data->render_size .y;
	t_color			*shared;
	size_t			i;
	t_color			color;

	shared = (t_color *)data->img->data;
#pragma omp parallel shared(shared, size) private(i, color)
	{
#pragma omp for schedule(dynamic)
		for (i = 0; i < size; ++i)
		{
			const int	oversample = (0.1 + data->oversampling_data[i]);
			if (oversample == 0)
				continue ;
			const	float factor = 1.f / (2.f * oversample + 1.f);
			const t_pos pos = (t_pos){i % data->viewport->size.x,
				i / data->viewport->size.x};
			float			cols[3];
			cols[0] = cols[1] = cols[2] = 0.f;
			for (int y = -oversample; y <= oversample; ++y)
			{
				for (int x = -oversample; x <= oversample; ++x)
				{
					const t_vec2d z = data->viewport->screen_to_space(
						data->viewport, (t_vec2d){(pos.x + x * factor) / data->render_size.x, (pos.y + y * factor) / data->render_size.y}
					);
					color = shader(z.x + I * z.y, closure);
					const float f = gauss_sample_weight(oversample * 2 + 1, x, y);
					cols[0] += color.channels.r / 255.f * f;
					cols[1] += color.channels.g / 255.f * f;
					cols[2] += color.channels.b / 255.f * f;
				}
			}
			((t_color *)shared)[i].channels.r = cols[0]  * 255.f;
			((t_color *)shared)[i].channels.g = cols[1]  * 255.f;
			((t_color *)shared)[i].channels.b = cols[2]  * 255.f;
		}
#pragma omp barrier
	}
}


void
	viewport_fragment(
		struct s_fragment_data *data,
		t_color (*shader)(double _Complex z, void *data),
		void *closure)
{
	const size_t	size = data->render_size.x * data->render_size.y;
	size_t			i;
	t_vec2d			z;
	t_color			*shared;

	if (data->oversampling_data)
	{
		fragment_oversample(data, shader, closure);
		return ;
	}
	shared = (t_color *)data->img->data;
#pragma omp parallel shared(shared, size) private(i, z)
	{
#pragma omp for schedule(dynamic)
		for (i = 0; i < size; ++i)
		{
			if (data->post_pass && shared[i].color != data->dafault_color.color)
				continue;
			z = data->viewport->screen_to_space(data->viewport, (t_vec2d){(i % data->render_size.x) / (double)data->render_size.x, (i / (double)data->render_size.x) / data->render_size.y });
			shared[i] = shader(z.x + I * z.y, closure);
		}
#pragma omp barrier
	}
}
