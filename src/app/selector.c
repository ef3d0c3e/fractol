/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"
#include "kernel/color.h"
#include "kernel/gradient.h"
#include "kernel/kernel.h"
#include "ui/draw.h"
#include "ui/event.h"
#include <stddef.h>

static bool	draw_item(t_fractol *f, t_pos id, const char *name)
{
	t_color	color;

	color.color = 0xFFFFFF;
	if (id.x == f->selector_pos.x && id.y == f->selector_pos.y)
		color.color = 0x00FF00;
	if (id.x == 0 && id.y == f->kernel_id)
		color.color = 0xFF0000;

	drawqueue_push(&f->ui.ui_queue, (t_draw_item){
			.item = DRAW_TEXT_SHADOW,
			.draw.text_shadow = {
				.color = color_lerp(color, (t_color){0}, 0.33 * (id.x != f->selector_pos.x)).color,
				.shadow = 0,
				.pos = {12 + 256 * id.x, 12 * (id.y - f->selector_pos.y + 3)},
				.str = name,
			}
	});
	return (ev_key_pressed(&f->ui, KEY_RETURN) && f->selector_pos.x == id.x && f->selector_pos.y == id.y);
}

void		fractol_selector(t_fractol *f)
{
	static const t_color	colors[] = {{0xFFFFFF}, {0x00FF00}, {0x0000FF}};
	const char				*name;
	int						id;

	if (ev_key_pressed(&f->ui, KEY_S))
		f->selector_shown = !f->selector_shown;
	if (!f->selector_shown)
		return ;
	f->selector_pos.y += ev_key_held(&f->ui, KEY_ARROW_DOWN) - ev_key_held(&f->ui, KEY_ARROW_UP);
	f->selector_pos.x += ev_key_held(&f->ui, KEY_ARROW_RIGHT) - ev_key_held(&f->ui, KEY_ARROW_LEFT);
	f->selector_pos.x = min(max(f->selector_pos.x, 0), 1);
	if (f->selector_pos.x == 0)
		f->selector_pos.y = min(max(f->selector_pos.y, 0), f->kernel_count - 1);
	if (f->selector_pos.x == 1)
		f->selector_pos.y = min(max(f->selector_pos.y, 0), 7);
	id = 0;
	while ((name = kernel_name(id)))
	{
		
		if (draw_item(f, (t_pos){0, id}, name) && f->kernel_id != f->selector_pos.y)
		{
			kernel_deinit(f->kernel, &f->kernel_settings);
			f->kernel_id = f->selector_pos.y;
			if (f->has_next_view)
				f->view = f->next_view;
			f->kernel = kernel_init(f->kernel_id, &f->view, &f->kernel_settings);
			f->next_view = f->view;
			f->needs_render = true;
		}
		++id;
	}
	if (draw_item(f, (t_pos){1, 0}, "Render"))
		f->needs_render = true;
	if (draw_item(f, (t_pos){1, 1}, "Upsample"))
		f->needs_resample = true;
	if (draw_item(f, (t_pos){1, 2}, "Randomize Gradient") && f->kernel->flags & USE_GRADIENT)
		gradient_randomize(&f->kernel_settings.gradient, 8);
	if (draw_item(f, (t_pos){1, 3}, "Reset viewport"))
	{
		f->view.view = (t_mat2d){{
			-(double)f->ui.size.x / f->ui.size.y,
			(double)f->ui.size.x / f->ui.size.y,
			f->kernel->default_viewport.data[2],
			f->kernel->default_viewport.data[3],
		}};
		f->next_view = f->view;
		f->has_next_view = false;
		f->needs_render = true;
	}
	if (draw_item(f, (t_pos){1, 4}, "Sceenshot to 'screenshot.ppm'"))
		fractol_screenshot(f);
	if (draw_item(f, (t_pos){1, 5}, "Iter +100"))
		f->max_iter = min(f->max_iter + 100, 20000);
	if (draw_item(f, (t_pos){1, 6}, "Iter -100"))
		f->max_iter = max(f->max_iter - 100, 1);
	if (draw_item(f, (t_pos){1, 7}, "Oversampling Debug"))
		f->needs_resample_debug = true;
	if (draw_item(f, (t_pos){1, 8}, "Gradient Debug") && f->kernel->flags & USE_GRADIENT)
		f->needs_gradient_debug = true;
	
	drawqueue_push(&f->ui.ui_queue, (t_draw_item){
		.item = DRAW_TEXT_SHADOW,
		.draw.text_shadow = {
			.color = colors[1].color,
			.shadow = 0,
			.pos = {256 * f->selector_pos.x, 12 * 3},
			.str = "->",
		}
	});
}
