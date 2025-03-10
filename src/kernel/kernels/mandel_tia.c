/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel_tia.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Render the Mandelbrot set using triangle inequality
 */

#include <kernel/kernel.h>

#include <complex.h>

static inline t_color	iter(double _Complex c, const t_closure *data)
{
	double _Complex	z;
	int				i;
	double			avg;
	double			last;
	double			frac;

	z = 0;
	i = 0;
	avg = 0;
	last = 0;
	while (i < data->max_it)
	{
		z = z * z + c;
		++i;
		last = 0.5 + 0.5 * sin(1.699587 * atan2(cimag(z), creal(z)));
		avg += last;
		if (cabs(z) >= 1e8)
			break ;
	}
	frac = 1 + log2(log(1e8) / log(cabs(z)));
	frac = frac * (avg / i) + (1.0 - frac) * (avg - last) / (i - 1.0);
	if (i < data->max_it)
		return (gradient_get(&data->settings->gradient, sqrt(fmin(
						fmax(frac * 8.117, 0.0), 10000.0))));
	return ((t_color){0});
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
	viewport_fragment(data, (t_color (*)(double _Complex, void *))iter,
		&closure);
}

const t_kernel	*mandel_tia(t_kernel_settings *settings)
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
		.name = "Mandelbrot Triangle Inequality",
		.render = render,
		.default_viewport = {{-1.5, 1.5, -1.0, 1.0}},
		.default_mat = {{1, 0, 0, 1}},
		.flags = USE_GRADIENT,
		.default_color = {0x000000},
	};

	if (settings)
		settings->gradient = gradient_new(colors,
				sizeof(colors) / sizeof(colors[0]));
	return (&kernel);
}
