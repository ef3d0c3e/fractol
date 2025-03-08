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

	if (size == 1)
		return (1.f);
	else if (size <= 15)
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
	float			weight;

	shared = (t_color *)data->img->data;
#pragma omp parallel for schedule(dynamic) shared(shared, size)\
	private(i, color, weight)
	for (size_t i = 0; i < size; ++i)
	{
		const int oversample = data->oversampling_data[i] * data->oversampling_factor;
		const double factor = 1.f / (2.f * oversample + 1.f);
		const t_pos pos = (t_pos){i % data->viewport->size.x, i / data->viewport->size.x};
		float cols[3] = {0.f, 0.f, 0.f};

		if (oversample < 0)
			continue;
		float weight_sum = 0.f;
		const int total_samples = (2 * oversample + 1) * (2 * oversample + 1);
		for (int sample = 0; sample < total_samples; ++sample)
		{
			int x = (sample % (2 * oversample + 1) - oversample);
			int y = (sample / (2 * oversample + 1) - oversample);
			t_vec2d z = data->viewport->screen_to_space(data->viewport, (t_vec2d){
					(pos.x + 0.5 + x * factor) / (float)data->render_size.x,
					(pos.y + 0.5 + y * factor) / (float)data->render_size.y});
			t_color color = shader(z.x + I * z.y, closure);

			float f = gauss_sample_weight(oversample * 2 + 1, x, y);
			cols[0] += color.channels.r / 255.f * f;
			cols[1] += color.channels.g / 255.f * f;
			cols[2] += color.channels.b / 255.f * f;
			weight_sum += f;
		}
		((t_color *)shared)[i].channels.r = cols[0] * 255.f / weight_sum;
		((t_color *)shared)[i].channels.g = cols[1] * 255.f / weight_sum;
		((t_color *)shared)[i].channels.b = cols[2] * 255.f / weight_sum;
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
			z = data->viewport->screen_to_space(data->viewport, (t_vec2d){((double)(i % data->render_size.x) + 0.5) / data->render_size.x, ((double)i + 0.5) / data->render_size.x / data->render_size.y });
			shared[i] = shader(z.x + I * z.y, closure);
		}
#pragma omp barrier
	}
}
