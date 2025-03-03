/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "kernel/color.h"
#include <kernel/kernel.h>
#include <complex.h>

static inline t_color	iter(
		t_pos pos,
		double _Complex c,
		const t_closure *data)
{
	int				i;
	double _Complex z;
	double _Complex dz;
	const double ratio = (data->view->view.data[1] - data->view->view.data[0]) / (data->view->size.x / 4.0);

	z = c;
	dz = 1;
	double k = 0;
	i = 0;
	while (i < data->max_it)
	{
		dz = 2 * dz * z + 1;
		z = z * z + data->settings->zparam;
		double m = cabs(z);
		k += exp(-m);
		if (m >= 1e8)
		{
			// color
			double hue = 0, sat = 0, val = 1; // interior color = white

			if (k < data->max_it)
			{ // exterior and boundary color
				double _Complex de = 2 * z * log(cabs(z)) / dz;
				hue = fmod(1 + carg(de) / (2 * M_PI), 1); // ? slope of de
				sat = 0.25;
				val = tanh(cabs(de) / ratio);
			}

			return color_from_hsv(hue, sat, val);
		}
		++i;
	}
	return ((t_color){0xFFFFFF});
}

static inline void
	render(
			struct s_fragment_data *data,
			const t_kernel_settings *settings,
			const int max_it
			)
{
	struct s_kernel_closure	closure;

	closure.view = data->viewport;
	closure.settings = settings;
	closure.max_it = max_it,
	viewport_fragment(data, (void *)iter, &closure);
}

const t_kernel	*julia_arg(t_kernel_settings *settings)
{
	static const t_kernel	kernel = {
		.name = "Julia Argument",
		.render = render,
		.default_viewport = {{-1.5, 1.5, -1.0, 1.0}},
		.default_mat = {{1, 0, 0, 1}},
		.flags = USE_ZPARAM,
		.default_color = {0xFFFFFF},
	};
	return (&kernel);
}
