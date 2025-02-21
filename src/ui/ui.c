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
#include "kernel/sobel.h"
#include <ui/ui.h>
#include <ui/event.h>
#include <app/fractol.h>
#include <mlx.h>

t_ui	ui_init(t_fractol *f, const t_pos size)
{
	size_t	i;
	t_ui	ui;

	i = 0;
	while (kernel_name(i))
		++i;
	event_setup(f);
	ui.mouse_down = false,
	ui.img_pos = pos_new(0, 0),
	ui.mouse_pos = pos_new(0, 0),
	ui.mouse_delta = pos_new(0, 0),
	ui.kernel_count = i,
	ui.selector_id = 0,
	ui.selector_shown = true,
	ui.size = size,
	ui.needs_render = true;
	ui.needs_resample = false;
	ui.render = mlx_new_image(f->mlx, size.x, size.y);
	ui.filter_buffer = malloc(size.x * size.y * 16);
	ui.ui_queue = drawqueue_new();
	return (ui);
}

void	ui_deinit(t_fractol *f, t_ui *ui)
{
	mlx_destroy_image(f->mlx, ui->render);
	drawqueue_free(&ui->ui_queue);
	free(ui->filter_buffer);
}

int	ui_draw(t_fractol *f)
{
	struct s_fragment_data	data;

	if (f->ui.needs_render)
	{
		f->ui.img_pos = pos_new(0, 0);
		f->last_view = f->view;
		data = (struct s_fragment_data){
			.viewport = &f->view,
			.oversampling_data = NULL,
			.img = f->ui.render
		};
		f->kernel->render(&data, &f->kernel_settings, 5000);
		f->ui.needs_render = false;
	}
	else if (f->ui.needs_resample)
	{
		data = (struct s_fragment_data){ &f->view, f->ui.render, sobel(f->ui.render, f->ui.filter_buffer) };
		f->kernel->render(&data, &f->kernel_settings, 5000);
		f->ui.needs_resample = false;
	}

	// Kernel name
	const char *name;
	if (f->ui.selector_shown)
	{
		if (f->ui.selector_id < 0)
			f->ui.selector_id = 0;
		if (f->ui.selector_id >= (int)f->ui.kernel_count)
			f->ui.selector_id = f->ui.kernel_count - 1;
		int	id = 0;
		while ((name = kernel_name(id)))
		{
			drawqueue_push(&f->ui.ui_queue, (t_draw_item){
				.item = DRAW_TEXT,
				.draw.text = {
					.color = 0x00FFFF * (f->ui.selector_id != id) + 0xFF0000 * (f->ui.selector_id == id),
					.pos = {12, 12 * (id - f->ui.selector_id + 3)},
					.str = name,
				}
			});
			++id;
		}
		drawqueue_push(&f->ui.ui_queue, (t_draw_item){
			.item = DRAW_TEXT,
			.draw.text = {
				.color = 0x7FFF7F,
				.pos = {3, 12 * 3},
				.str = ">",
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
