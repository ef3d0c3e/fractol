/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_de.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Render the Julia set using complex argument coloring
 */

#include <kernel/kernel.h>

#include <complex.h>

static inline t_color	iter(
		double _Complex c,
		const t_closure *data)
{
	int				i;
	double			m;
	double _Complex	z;
	double _Complex	dz;

	z = c;
	dz = 1;
	i = 0;
	while (i < data->max_it)
	{
		dz = 2 * dz * z + 1;
		z = z * z + data->settings->zparam;
		m = cabs(z);
		if (m >= 1e8)
		{
			m = 2 * log2(m) * m / cabs(dz);
			return (gradient_get(&data->settings->gradient, 0.1 * log(m)));
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
	viewport_fragment(data, (t_color (*)(double _Complex, void *))iter,
		&closure);
}

const t_kernel	*julia_de(t_kernel_settings *settings)
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
		.name = "Julia Distance Estimage",
		.render = render,
		.default_viewport = {{-1.5, 1.5, -1.0, 1.0}},
		.default_mat = {{1, 0, 0, 1}},
		.flags = USE_ZPARAM | USE_GRADIENT,
		.default_color = {0x000000},
	};

	if (settings)
		settings->gradient
			= gradient_new(colors, sizeof(colors) / sizeof(colors[0]));
	return (&kernel);
}
