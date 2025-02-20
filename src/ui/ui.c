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
	event_setup(f);
	return ((t_ui){
		.needs_render = true,
		.mouse_down = false,
		.img_pos = pos_new(0, 0),
		.mouse_pos = pos_new(0, 0),
		.mouse_delta = pos_new(0, 0),
		.size = size,
		.render = mlx_new_image(f->mlx, size.x, size.y),
		.ui_queue = drawqueue_new(),
	});
}

void	ui_deinit(t_fractol *f, t_ui *ui)
{
	mlx_destroy_image(f->mlx, ui->render);
	drawqueue_free(&ui->ui_queue);
}

int	ui_draw(t_fractol *f)
{
	if (f->ui.needs_render)
	{
		f->last_view = f->view;
		f->kernel->render(&f->view, &f->kernel_settings, f->ui.render, 500);
		f->ui.needs_render = false;
	}

	// Kernel name

	size_t	id = 0;
	const char *name;
	while ((name = kernel_name(id++)))
	{
		drawqueue_push(&f->ui.ui_queue, (t_draw_item){

			.item = DRAW_TEXT,
			.draw.text = {
				.color = 0x00FFFF,
				.pos = {32, 32},
				.str = name,
			}
		});
	}
	//static const char *t = "TEST";
	mlx_clear_window(f->mlx, f->window);
	mlx_put_image_to_window(f->mlx, f->window, f->ui.render,
		f->ui.img_pos.x, f->ui.img_pos.y);
	drawqueue_render(&f->ui.ui_queue, f->mlx, f->window);
	drawqueue_clear(&f->ui.ui_queue);
	return (0);
}
