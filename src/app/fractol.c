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

/**
 * @brief Fractol initialization
 */

#include <app/fractol.h>

#include <ft_printf.h>
#include <complex.h>
#include <mlx.h>

/* Initialize mlx */
static inline void	init_mlx(t_fractol *f, t_pos size)
{
	f->mlx = mlx_init();
	f->window = mlx_new_window(f->mlx, size.x, size.y, "Fractol");
}

/* Initialize rendering kernel */
static inline void	init_kernel(t_fractol *f, t_pos size, int kernel_id)
{
	f->view.size = size;
	f->view.view = (t_mat2d){{
		-(double)size.x / size.y,
		(double)size.x / size.y,
		-1.0,
		1.0
	}};
	f->view.data = NULL;
	f->kernel_count = 0;
	while (kernel_name(f->kernel_count))
		++f->kernel_count;
	if (kernel_id >= f->kernel_count)
		exit((ft_dprintf(2, "Error: Wrong id for kernel: %d. Expected a value "
					"between 0 and %d.\n", kernel_id, f->kernel_count - 1), 1));
	f->kernel_id = kernel_id;
	f->kernel_settings.zparam = -0.8 + I * 0.156;
	f->kernel = kernel_init(f->kernel_id, &f->view, &f->kernel_settings);
	f->next_view = f->view;
	f->has_next_view = false;
	f->post_pass = false;
	f->max_iter = 500;
}

/* Start program loop */
static void	fractol_loop(t_fractol *f)
{
	fractol_selector(f);
	fractol_ui(f);
	fractol_move(f);
	fractol_zparam(f);
	fractol_render(f);
}

/* Initializes fractol's ui */
static inline void	init_ui(t_fractol *f, t_pos size)
{
	f->ui = ui_init(f, size);
	f->ui.ui_loop = fractol_loop;
	f->selector_pos = (t_pos){0, f->kernel_id};
	f->selector_shown = true;
	f->needs_render = false;
	f->needs_resample = false;
	f->needs_resample_debug = false;
	f->needs_gradient_debug = false;
	f->filter_buffer = malloc(sizeof(float) * size.x * size.y * 4);
}

void	fractol_start(
	t_pos win_size,
	int downsampling,
	int kernel,
	int oversampling)
{
	t_fractol	f;

	f.downsampling = downsampling;
	f.oversampling = oversampling;
	init_kernel(&f, win_size, kernel);
	init_mlx(&f, win_size);
	init_ui(&f, win_size);
	ui_update(&f);
	mlx_loop(f.mlx);
	ui_deinit(&f, &f.ui);
	kernel_deinit(f.kernel, &f.kernel_settings);
	free(f.filter_buffer);
	viewport_free(&f.view);
	mlx_destroy_window(f.mlx, f.window);
	free(f.mlx);
}
