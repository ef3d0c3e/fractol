/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatou.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "kernel/color.h"
#include "kernel/gradient.h"
#include <kernel/kernel.h>
#include <complex.h>

static inline t_color	iter(double _Complex c, const t_closure *data)
{
	static const double _Complex	roots[] = {1.0,
		-0.5 + I * sqrt(3) / 2, -0.5 - I * sqrt(3) / 2};
	int								i;
	size_t							k;
	double _Complex					z;

	z = c;
	i = 0;
	while (i < data->max_it)
	{
		z -= (z * z * z - 1) / (3 * z * z);
		k = 0;
		while (k < sizeof(roots) / sizeof(roots[0]))
		{
			if (cabs(z - roots[k]) < 1e-8)
				return (gradient_get(&data->settings->gradient, k / 2.0));
			++k;
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
	closure.max_it = max_it;
	viewport_fragment(data, (void *)iter, &closure);
}

const t_kernel	*fatou(t_kernel_settings *settings)
{
	static const struct s_gr_color	colors[] = {
	{{0xFF0000}, 1.0}, {{0x00FF00}, 1.0}, {{0x0000FF}, 1.0}};
	static const t_kernel			kernel = {
		.name = "Fatou",
		.render = render,
		.default_viewport = {{-1.5, 1.5, -1.0, 1.0}},
		.default_mat = {{1, 0, 0, 1}},
		.flags = USE_GRADIENT,
		.default_color = {0x000000},
	};

	if (settings)
		settings->gradient
			= gradient_new(colors, sizeof(colors) / sizeof(colors[0]));
	return (&kernel);
}
