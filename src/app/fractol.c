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
#include "viewport/viewport_linear.h"
#include <mlx.h>

static void pmat(const t_mat2d *mat)
{
	printf("[[%F %F] [%F %F]]", mat->data[0], mat->data[1], mat->data[2], mat->data[3]);
}

t_fractol fractol_init()
{
	const t_pos	size = pos_new(1920, 1080);
	t_fractol	s;

	/// MLX_INIT
	s.mlx = mlx_init();
	s.window = mlx_new_window(s.mlx, size.x, size.y, "Fractol");

	s.ui = ui_init(&s, size);
	s.kernel = kernel_init(0, size, &s.view, &s.kernel_settings);
	//pmat(&((struct s_viewport_linear_data*)s.view.data)->mat);
	printf("\n");
	s.last_view = s.view;

	ui_draw(&s);
	mlx_loop(s.mlx);

	ui_deinit(&s, &s.ui);
	viewport_free(&s.view);
	mlx_destroy_window(s.mlx, s.window);
	free(s.mlx);

	return (s);
}
