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
#include "viewport/viewport_linear.h"
#include <mlx.h>

t_fractol fractol_init()
{
	t_fractol	s;

	/// MLX_INIT
	s.mlx = mlx_init();
	s.window = mlx_new_window(s.mlx, 1920, 1080, "Fractol");

	s.ui = ui_init(&s, (t_pos){1920, 1080});

	// Viewport
	struct s_viewport_linear_data view_data = view_linear_data(
			(t_mat2d){{ 1.0, 0.0, 0.0, 1.0 }});
	s.view = viewport_create(
			pos_new(1920, 1080),
			view_linear_screen_to_space,
			view_linear_space_to_screen,
			&view_data);
	s.last_view = s.view;
	s.kernel = mandel_ext_de;

	ui_draw(&s);
	mlx_loop(s.mlx);

	ui_deinit(&s, &s.ui);
	mlx_destroy_window(s.mlx, s.window);
	free(s.mlx);

	return (s);
}
