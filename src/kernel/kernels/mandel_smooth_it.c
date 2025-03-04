/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel_smooth_it.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "app/viewport/viewport.h"
#include <kernel/kernel.h>

static inline t_color	iter(t_vec2d c, const t_closure *data)
{
	int				i;
	double			m;
	t_vec2d			z;

	z = (t_vec2d){0, 0};
	i = 0;
	while (i < data->max_it)
	{
		z = (t_vec2d){
			z.x * z.x - z.y * z.y + c.x,
			2.0 * z.x * z.y + c.y,
		};
		m = z.x * z.x + z.y * z.y;
		if (m >= 1e8)
		{
			m = log2(-log((double)i / data->max_it)) - log2(0.5 * log(m));
			return (gradient_get(&data->settings->gradient, (i + 1 + m) / 20));
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

const t_kernel	*mandel_smooth_it(t_kernel_settings *settings)
{
	static const struct s_gr_color	colors[] = {
	{{0x061F42}, 1.0f}, {{0x230F27}, 1.0f}, {{0x098FE5}, 1.0f},
	{{0xD6F1D2}, 1.0f}, {{0xFFFCC0}, 1.0f}, {{0x061F42}, 1.0f},
	};
	static const t_kernel			kernel = {
		.name = "Mandelbrot Smooth Iteration Count",
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
