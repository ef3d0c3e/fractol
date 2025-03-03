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
#include "kernel/color.h"
#include <kernel/kernel.h>
#include <complex.h>

static inline t_color iter(t_pos pos, double _Complex c, const t_closure *data)
{
	const int max_ref_it = creal(*((const double _Complex *)data->data));
	const double _Complex *refs = ((const double _Complex *)data->data) + 1;


	double _Complex dz = 0;
	double _Complex dc = c - refs[0];
	int iter = 0;
	int ref_iter = 0;
	double dist = 0;
	while (iter < data->max_it) {
		// pt: the perturbation iteration equation
		dz = 2 * dz * refs[ref_iter] + dz * dz + dc;
		++ref_iter;

		// pt: add the delta orbit to the reference orbit
		double _Complex z = refs[ref_iter] + dz;
		// pt: if the combined reference and delta orbit escapes, bail out
		dist += exp(-cabs(z));
		if (cabs(z) > 1000) {
			return (gradient_get(&data->settings->gradient, log(dist)));
		};
		// pt: if the delta is larger than the reference, or of the
		//       reference orbit has already escaped, reset back to
		//       the beginning of the SAME reference orbit!
		if (cabs(z) < cabs(dz) || ref_iter == max_ref_it) {
			dz = z;
			ref_iter = 0;
		}
		iter++;
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
	t_vec2d					center;
	double _Complex			*refs;
	struct s_kernel_closure	closure;

	refs = malloc(sizeof(double _Complex) * (max_it + 1));
	center = data->viewport->screen_to_space(data->viewport, (t_pos){data->viewport->size.x / 2, data->viewport->size.y / 2}, (t_vec2d){0, 0});
	closure.view = data->viewport;
	closure.settings = settings;
	closure.max_it = max_it;
	closure.data = refs;

	double _Complex z = 0;
	refs[0] = max_it;
	for (int i = 1; i < max_it + 1; ++i)
	{
		refs[i] = z;
		z = z*z + center.x + I * center.y;
		if (cabs(z) >= 1000)
		{
			refs[0] = i;
			break;
		}
    }
	viewport_fragment(data, (void *)iter, &closure);
	free(refs);
}

const t_kernel	*mandel_exp_pt(t_kernel_settings *settings)
{
	static const struct s_gr_color	colors[] = {
    {{66 << 16 | 30 << 8 | 15}, 1.0},{{25 << 16 | 7 << 8 | 26}, 1.0},
    {{9 << 16 | 1 << 8 | 47}, 1.0},{{4 << 16 | 4 << 8 | 73}, 1.0},
    {{0 << 16 | 7 << 8 | 100}, 1.0},{{12 << 16 | 44 << 8 | 138}, 1.0},
    {{24 << 16 | 82 << 8 | 177}, 1.0},{{57 << 16 | 125 << 8 | 209}, 1.0},
    {{134 << 16 | 181 << 8 | 229}, 1.0},{{211 << 16 | 236 << 8 | 248}, 1.0},
    {{241 << 16 | 233 << 8 | 191}, 1.0},{{248 << 16 | 201 << 8 | 95}, 1.0},
    {{255 << 16 | 170 << 8 | 0}, 1.0},{{204 << 16 | 128 << 8 | 0}, 1.0},
    {{153 << 16 | 87 << 8 | 0}, 1.0},{{106 << 16 | 52 << 8 | 3}, 1.0},
    {{66 << 16 | 30 << 8 | 15}, 1.0}};
	static const t_kernel	kernel = {
		.name = "Mandelbrot Exponential PT",
		.render = render,
		.default_viewport = {{-1.5, 1.5, -1.0, 1.0}},
		.default_mat = {{1, 0, 0, 1}},
		.flags = USE_GRADIENT,
		.default_color = {0x000000},
	};
	if (settings)
		settings->gradient = gradient_new(colors, sizeof(colors) / sizeof(colors[0]));
	return (&kernel);
}
