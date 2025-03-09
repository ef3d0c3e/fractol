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

static inline t_color
	adaptive_sample(
		struct s_fragment_data *data,
		size_t ids[2],
		t_color (*shader)(double _Complex z, void *data),
		void *closure)
{
	const int		oversample = data->oversampling_data[ids[0]]
		* data->oversampling_factor;
	const double	factor = 1.0 / (2.0 * oversample + 1.0);
	const t_pos		delta = (t_pos){ids[1] % (2 * oversample + 1) - oversample,
		ids[1] / (2 * oversample + 1) - oversample};
	const t_vec2d	z = data->viewport->screen_to_space(data->viewport,
			(t_vec2d){
			((ids[0] % data->viewport->size.x) + 0.5 + delta.x * factor)
			/ (float)data->render_size.x,
			((ids[0] / data->viewport->size.x) + 0.5 + delta.y * factor)
			/ (float)data->render_size.y});

	return (shader(z.x + I * z.y, closure));
}

/* Gaussian average over the samples */
static inline t_color
	oversample_average(
		struct s_fragment_data *data,
		size_t idx,
		t_color (*shader)(double _Complex z, void *data),
		void *closure)
{
	const int	oversample = data->oversampling_data[idx]
		* data->oversampling_factor;
	size_t		i;
	t_color		pix;
	float		colors[5];

	colors[0] = 0.f;
	colors[1] = 0.f;
	colors[2] = 0.f;
	colors[3] = 0.f;
	i = 0;
	while (i++ < (2 * oversample + 1) * (2 * oversample + 1))
	{
		pix = adaptive_sample(data, (size_t [2]){idx, i - 1}, shader, closure);
		colors[4] = gauss_sample_weight(oversample * 2 + 1,
				i % (2 * oversample + 1), i / (2 * oversample + 1));
		colors[0] += pix.channels.r / 255.f * colors[4];
		colors[1] += pix.channels.g / 255.f * colors[4];
		colors[2] += pix.channels.b / 255.f * colors[4];
		colors[3] += colors[4];
	}
	pix.channels.r = colors[0] * 255.f / colors[3];
	pix.channels.g = colors[1] * 255.f / colors[3];
	pix.channels.b = colors[2] * 255.f / colors[3];
	return (pix);
}

static void	
	fragment_oversample(
		struct s_fragment_data *data,
		t_color (*shader)(double _Complex z, void *data),
		void *closure)
{
	const size_t	size = data->render_size.x * data->render_size.y;
	t_color			*shared;
	size_t			i;

	shared = (t_color *)data->img->data;
	FRACTOL_OMP("omp parallel for schedule(dynamic) shared(shared) private(i)",
		i, size, FRACTOL_EXPAND({
			if (data->oversampling_data[i] * data->oversampling_factor < 0)
			continue;
		shared[i] = oversample_average(data, i, shader, closure);
	}));
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
	FRACTOL_OMP("omp parallel for schedule(dynamic) shared(shared)\
		private(i, z)", i,
		size, FRACTOL_EXPAND({
			if (data->post_pass && shared[i].color != data->dafault_color.color)
			continue;
			z = data->viewport->screen_to_space(data->viewport, (t_vec2d){
				((double)(i % data->render_size.x) + 0.5) / data->render_size.x,
				((double)i + 0.5) / data->render_size.x / data->render_size.y});
			shared[i] = shader(z.x + I * z.y, closure);
	}));
}
