/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship_de.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "kernel/gradient.h"
#include "util/matrix.h"
#include "util/vector.h"
#include <app/viewport/viewport.h>
#include <complex.h>
#include <kernel/kernel.h>

static inline void	update_jn(t_mat2d *j, double _Complex z)
{
	*j = (t_mat2d){{2 * creal(z) * j->data[0] - 2 * cimag(z) * j->data[2] + 1,
		2 * creal(z) * j->data[1] - 2 * cimag(z) * j->data[3],
		2 * fabs(creal(z)) * fsign(cimag(z)) * j->data[2]
		+ 2 * fabs(cimag(z)) * fsign(creal(z)) * j->data[0],
		2 * fabs(creal(z)) * fsign(cimag(z)) * j->data[3]
		+ 2 * fabs(cimag(z)) * fsign(creal(z)) * j->data[1] + 1}};
}

static inline t_color	iter(double _Complex c, const t_closure *data)
{
	int				i;
	double _Complex	z;
	t_mat2d			j;
	t_vec2d			uv;
	double			m;

	z = 0;
	j = (t_mat2d){{0, 0, 0, 0}};
	i = 0;
	while (i < data->max_it)
	{
		update_jn(&j, z);
		z = fabs(creal(z)) + I * fabs(cimag(z));
		z = z * z + c;
		m = creal(z) * creal(z) + cimag(z) * cimag(z);
		if (m >= 1e16)
		{
			uv = (t_vec2d){creal(z), cimag(z)};
			uv = vec_mul_mat(&uv, &j);
			return (gradient_get(&data->settings->gradient,
					log10(m * 0.5 * log(m) / vec_norm(&uv))));
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
	closure.max_it = max_it;
	viewport_fragment(data, (void *)iter, &closure);
}

const t_kernel	*burning_ship_de(t_kernel_settings *settings)
{
	static const struct s_gr_color	colors[] = {
	{{66 << 16 | 30 << 8 | 15}, 1.0},
	{{25 << 16 | 7 << 8 | 26}, 1.0}, {{9 << 16 | 1 << 8 | 47}, 1.0},
	{{4 << 16 | 4 << 8 | 73}, 1.0}, {{0 << 16 | 7 << 8 | 100}, 1.0},
	{{12 << 16 | 44 << 8 | 138}, 1.0}, {{24 << 16 | 82 << 8 | 177}, 1.0},
	{{57 << 16 | 125 << 8 | 209}, 1.0}, {{134 << 16 | 181 << 8 | 229}, 1.0},
	{{211 << 16 | 236 << 8 | 248}, 1.0}, {{241 << 16 | 233 << 8 | 191}, 1.0},
	{{248 << 16 | 201 << 8 | 95}, 1.0}, {{255 << 16 | 170 << 8 | 0}, 1.0},
	{{204 << 16 | 128 << 8 | 0}, 1.0}, {{153 << 16 | 87 << 8 | 0}, 1.0},
	{{106 << 16 | 52 << 8 | 3}, 1.0}, {{66 << 16 | 30 << 8 | 15}, 1.0}};
	static const t_kernel			kernel = {
		.name = "Burning Ship Distance Estimate",
		.render = render,
		.default_viewport = {{-1.5, 1.5, -1.0, 1.0}},
		.default_mat = {{1, 0, 0, -1}},
		.flags = USE_GRADIENT,
		.default_color = {0x000000},
	};

	if (settings)
		settings->gradient = gradient_new(colors,
				sizeof(colors) / sizeof(colors[0]));
	return (&kernel);
}
