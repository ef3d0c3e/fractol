/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"
#include "app/viewport/viewport.h"
#include "kernel/kernel.h"
#include "util/matrix.h"
#include <mlx.h>

static inline void	init_mlx(t_fractol *f, t_pos size)
{
	f->mlx = mlx_init();
	f->window = mlx_new_window(f->mlx, size.x, size.y, "Fractol");
}

static inline void	init_kernel(t_fractol *f, t_pos size)
{
	f->view.size = size,
	f->view.view = (t_mat2d){{
		-(double)size.x / size.y,
		(double)size.x / size.y,
		-1.0,
		1.0
	}};
	f->kernel_id = 0;
	f->kernel = kernel_init(0, &f->view, &f->kernel_settings);
	f->last_view = f->view;
	f->kernel_count = 0;
	while (kernel_name(f->kernel_count))
		++f->kernel_count;
}

static void	fractol_loop(t_fractol *f)
{
	fractol_selector(f);
	fractol_move(f);
	/*fractol_bar(f)*/;
	fractol_render(f);
}

static inline void	init_ui(t_fractol *f, t_pos size)
{
	f->ui = ui_init(f, size);
	f->ui.ui_loop = fractol_loop;
	f->selector_id = 0;
	f->selector_shown = true;
	f->needs_render = false;
	f->needs_resample = false;
	f->filter_buffer = malloc(sizeof(float) * size.x * size.y * 4);
}

void fractol_run()
{
	const t_pos	size = pos_new(1920, 1080);
	t_fractol	f;

	init_mlx(&f, size);
	init_kernel(&f, size);
	init_ui(&f, size);

	//ui_update(&f);
	mlx_loop(f.mlx);

	ui_deinit(&f, &f.ui);
	kernel_deinit(f.kernel, &f.kernel_settings);
	free(f.filter_buffer);
	viewport_free(&f.view);
	mlx_destroy_window(f.mlx, f.window);
	free(f.mlx);
}
