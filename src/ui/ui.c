/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ui.h"
#include "ui/draw.h"
#include <app/fractol.h>
#include <mlx.h>

t_ui	ui_init(t_xvar *mlx, const t_pos size)
{
	return ((t_ui){
		.needs_render = true,
		.mouse_down = false,
		.img_pos = pos_new(0, 0),
		.mouse_pos = pos_new(0, 0),
		.mouse_delta = pos_new(0, 0),
		.render = mlx_new_image(mlx, size.x, size.y),
		.ui_queue = drawqueue_new(),
		
	});
}

void	ui_deinit(t_xvar *mlx, t_ui *ui)
{
	mlx_destroy_image(mlx, ui->render);
	drawqueue_free(&ui->ui_queue);
}

int	ui_draw(t_fractol *f)
{
	if (f->ui.needs_render)
	{
		f->last_view = f->view;
		f->kernel.render(&f->view, f->ui.render);
		f->ui.needs_render = false;
	}
	mlx_put_image_to_window(f->mlx, f->window, f->ui.render, f->ui.img_pos.x, f->ui.img_pos.y);
	drawqueue_render(&f->ui.ui_queue, f->mlx, f->window);
	return (0);
}
