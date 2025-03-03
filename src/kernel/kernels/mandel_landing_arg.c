/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel_ext_de.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "kernel/gradient.h"
#include "util/vector.h"
#include <app/viewport/viewport.h>
#include <complex.h>
#include <kernel/kernel.h>

static inline t_color iter(t_vec2d c, const t_closure *data)
{
	int				i;
	const double _Complex cc = *(double _Complex *)&c;
	double _Complex z;
	double _Complex dz;

	z = (double _Complex){0, 0};
	dz = (double _Complex){0, 0};
	i = 0;
	while (i < data->max_it)
	{
		dz = 2 * z * dz + 1;
		z = z * z + cc;
		double m = cabs(z);
		if (m >= 1e8)
		{
			double k = i + 1.0 - log(log(m))/log(2);
			double potential = pow(2,-k);
			z = potential * conj(z) * dz / (m*m*log(m));
			return (gradient_get(&data->settings->gradient, carg(z) / 6.28));
		}
		++i;
	}
	return ((t_color){0x000000});
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

const t_kernel	*mandel_landing_arg(t_kernel_settings *settings)
{
	static const struct s_gr_color	colors[] = {
		{{0xFFFFFF}, 1.0},
		{{0x000000}, 2.0},
	};
	static const t_kernel	kernel = {
		.name = "Mandelbrot Landing Arg",
		.render = render,
		.default_viewport = {{-1.5, 1.5, -1.0, 1.0}},
		.default_mat = {{1, 0, 0, 1}},
		.flags = USE_GRADIENT,
	};
	if (settings)
		settings->gradient = gradient_new(colors, sizeof(colors) / sizeof(colors[0]));
	return (&kernel);
}
