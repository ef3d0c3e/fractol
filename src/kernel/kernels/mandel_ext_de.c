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
#include <app/viewport/viewport.h>
#include <kernel/kernel.h>

static inline void	iter(t_pos pos, t_vec2d z, const t_closure *data)
{
	int				i;
	double			x;
	double			y;
	double			tmp;

	x = 0;
	y = 0;
	tmp = 0;
	i = 0;
	while (i < 100)
	{
		tmp = x;
		x = x * x - y * y + z.x;
		y = 2 * tmp * y + z.y;
		if (x * x + y * y >= 4)
		{
			image_pixel(data->img, pos, 0xFF0000);
			return ;
		}
		++i;
	}
	image_pixel(data->img, pos, 0x0000FF);
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
	const static struct s_gr_color	colors[] = {
		{{0xFF0000}, 1.f},
	};
	static const t_kernel	kernel = {
		.name = "Mandelbrot Exterior Distance Estimate",
		.render = render,
		.default_viewport = {{-1.5, 1.5, -1.0, 1.0}},
		.default_mat = {{1, 0, 0, 1}},
		.settings = { 
		}
	};
	//gradient_new(colors, sizeof(colors) / sizeof(colors[0]));
	return (&kernel);
}
