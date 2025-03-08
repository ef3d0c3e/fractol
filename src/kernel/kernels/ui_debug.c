/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "kernel/color.h"
#include "util/vector.h"
#include <app/viewport/viewport.h>
#include <complex.h>
#include <kernel/kernel.h>

static inline t_color	iter(double _Complex c, const t_closure *data)
{
	const double	ratio = (4.0 / data->view->size.x)
		* (data->view->view.data[1] - data->view->view.data[0]);
	const t_vec2d	d = {creal(c) - floor(creal(c)),
		cimag(c) - floor(cimag(c))};

	if (fabs(d.x) < ratio / 2 || fabs(d.y) < ratio / 2)
		return ((t_color){0x000000});
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
	closure.max_it = max_it;
	viewport_fragment(data, (t_color (*)(double _Complex, void*))iter, &closure);
}

const t_kernel	*ui_debug(t_kernel_settings *settings)
{
	static const t_kernel	kernel = {
		.name = "UI Debug",
		.render = render,
		.default_viewport = {{-1.5, 1.5, -1.0, 1.0}},
		.default_mat = {{1, 0, 0, 1}},
		.flags = 0,
		.default_color = {0x000000},
	};

	(void)settings;
	return (&kernel);
}
