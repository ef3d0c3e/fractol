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
#include "kernel/gradient.h"
#include "util/vector.h"
#include <app/viewport/viewport.h>
#include <complex.h>
#include <kernel/kernel.h>

static inline t_color	iter(double _Complex c, const t_closure *data)
{
	int				i;
	double _Complex z;

	t_vec2d d = { creal(c) - floor(creal(c)), (cimag(c) - floor(cimag(c))) };
	if (fabs(d.x) < 0.01 || fabs(d.y) < 0.01)
		return ((t_color){0x000000});
	return (color_lerp((t_color){0xFF0000}, (t_color){0xFFFFFF}, creal(c) / 5));
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
	return (&kernel);
}
