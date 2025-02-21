/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel_de.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <kernel/kernel.h>

static inline t_color
	iter(t_pos pos, t_vec2d c, const t_closure *data)
{
	int				i;
	double			m;
	t_vec2d			z;
	t_vec2d			d;

	z = c;
	d = (t_vec2d){1, 0};
	i = 0;
	while (i < data->max_it)
	{
		d = (t_vec2d){2 * (d.x * z.x - d.y * z.y) + 1,
			2 * (d.y * z.x + d.x * z.y)};
		z = (t_vec2d){z.x * z.x - z.y * z.y + c.x, 2.0 * z.x * z.y + c.y};
		m = z.x * z.x + z.y * z.y;
		if (m >= 1e16)
		{
			m = 2 * log2(sqrt(m)) * sqrt(m) / sqrt(pow(d.x, 2) + pow(d.y, 2));
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
	viewport_fragment(data, (void *)iter, &closure);
}

const t_kernel	*mandel_de(t_kernel_settings *settings)
{
	static const struct s_gr_color	colors[] = {
	{{0x061F42}, 1.0f},
	{{0x230F27}, 1.0f},
	{{0x098FE5}, 1.0f},
	{{0xD6F1D2}, 1.0f},
	{{0xFFFCC0}, 1.0f},
	{{0x061F42}, 1.0f},
	};
	static const t_kernel			kernel = {
		.name = "Mandelbrot Distance Estimate",
		.render = render,
		.default_viewport = {{-1.5, 1.5, -1.0, 1.0}},
		.default_mat = {{1, 0, 0, 1}},
		.flags = USE_GRADIENT,
	};

	if (settings)
		settings->gradient = gradient_new(colors,
				sizeof(colors) / sizeof(colors[0]));
	return (&kernel);
}
