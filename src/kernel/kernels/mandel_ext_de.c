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
#include <kernel/kernel.h>

static inline void	iter(t_pos pos, t_vec2d c, const t_closure *data)
{
	int				i;
	t_vec2d			z;

	z = c;
	i = 0;
	double	dist = 0;
	while (i < 500)
	{
		z = (t_vec2d){
			z.x * z.x - z.y * z.y + c.x,
			2.0 * z.x * z.y + c.y,
		};
		dist += exp(-sqrt(z.x * z.x + z.y * z.y));
		if (z.x * z.x + z.y * z.y >= 4)
		{
			float f = sqrt(log(1.0 + dist));
			image_pixel(data->img, pos,
				gradient_get(&data->settings->gradient, f)
			);
			return ;
		}
		++i;
	}
	image_pixel(data->img, pos, (t_color){0x000000});
	/*image_pixel(data->img, pos,
			gradient_get(&data->settings->gradient, pos.x / 1920.0)
			);*/
}

static inline void
	render(
			const struct s_viewport *viewport,
			const t_kernel_settings *settings,
			t_img *img
			)
{
	struct s_kernel_closure	closure;

	closure.view = viewport;
	closure.settings = settings;
	closure.img = img;
	viewport_foreach(viewport, (void *)iter, &closure);
}

const t_kernel	*mandel_ext_de(t_kernel_settings *settings)
{
	static const struct s_gr_color	colors[] = {
		{{0xFF0000}, .5f},
		{{0x00FF00}, 1.f},
		{{0x0000FF}, 1.f},
		{{0xFF0000}, .5f},
	};
	static const t_kernel	kernel = {
		.name = "Mandelbrot Exterior Distance Estimate",
		.render = render,
		.default_viewport = {{-1.5, 1.5, -1.0, 1.0}},
		.default_mat = {{1, 0, 0, 1}},
	};
	settings->gradient = gradient_new(colors, sizeof(colors) / sizeof(colors[0]));
	return (&kernel);
}
