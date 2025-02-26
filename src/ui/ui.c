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
#include "kernel/kernel.h"
#include <ui/ui.h>
#include <ui/event.h>
#include <app/fractol.h>
#include <mlx.h>

t_ui	ui_init(t_fractol *f, const t_pos size)
{
	t_ui	ui;

	event_setup(f);
	ui.mouse_down = false;
	ui.img_pos = pos_new(0, 0);
	ui.mouse_pos = pos_new(0, 0);
	ui.event.type = UI_NONE;
	ui.size = size;
	ui.render = mlx_new_image(f->mlx, size.x, size.y);
	ui.ui_queue = drawqueue_new();
	return (ui);
}

void	ui_deinit(t_fractol *f, t_ui *ui)
{
	mlx_destroy_image(f->mlx, ui->render);
	drawqueue_free(&ui->ui_queue);
}

void	ui_update(t_fractol *f)
{
	f->ui.ui_loop(f);
	mlx_clear_window(f->mlx, f->window);
	mlx_put_image_to_window(f->mlx, f->window, f->ui.render,
		f->ui.img_pos.x, f->ui.img_pos.y);
	drawqueue_render(&f->ui.ui_queue, f->mlx, f->window);
	drawqueue_clear(&f->ui.ui_queue);
}
