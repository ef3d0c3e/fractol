/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Handles mouse movements
 */

#include "app/viewport/viewport.h"
#include "fractol.h"
#include "ui/event.h"
#include "util/vector.h"
#include <complex.h>

void
	move_viewport(
	t_fractol *f,
	const t_pos start,
	const t_pos end,
	const int zoom_delta
	)
{
	t_viewport	*view;

	view = &f->view;
	if (f->has_next_view)
		view = &f->next_view;
	if (!zoom_delta && !f->has_next_view)
	{
		view_move(view,
			f->view.screen_to_space(view, (t_vec2d){start.x / (double)f->ui.size.x, start.y / (double)f->ui.size.x}),
			f->view.screen_to_space(view, (t_vec2d){end.x / (double)f->ui.size.x, end.y / (double)f->ui.size.x}),
			1.0);
	}
	if (zoom_delta)
	{
		if (!f->has_next_view)
			f->next_view = f->view;
		f->has_next_view = true;
		view_zoom(&f->next_view, f->view.screen_to_space(&f->view, (t_vec2d){end.x / (double)f->ui.size.x, end.y / (double)f->ui.size.y}), -zoom_delta);
	}
}

/* Displays reticles and move area */
static void move_reticle(t_fractol *f)
{
	double *data;
	
	data = f->view.view.data;
	if (f->has_next_view)
		data = f->next_view.view.data;
	t_pos tl = f->view.space_to_screen(&f->view,
			(t_vec2d){data[0], data[3]});
	t_pos br = f->view.space_to_screen(&f->view,
			(t_vec2d){data[1], data[2]});

	if (br.x <= tl.x)
		(tl.x ^= br.x, br.x ^= tl.x, tl.x ^= br.x);
	if (br.y <= tl.y)
		(tl.y ^= br.y, br.y ^= tl.y, tl.y ^= br.y);
	// Render rectangle
	drawqueue_push(&f->ui.ui_queue, (t_draw_item){
		.item = DRAW_RECT,
		.draw.rect = {
			.top_left = tl,
			.bottom_right = br,
			.color = 0x00FF00 + 0xFF * f->has_next_view,
			.fill = false,
		}
	});

	// Render reticle
	drawqueue_push(&f->ui.ui_queue, (t_draw_item){
		.item = DRAW_RECT,
		.draw.rect = {
			.top_left = {tl.x + (br.x - tl.x) / 2 - 8, tl.y + (br.y - tl.y) / 2 - 8},
			.bottom_right = {tl.x + (br.x - tl.x) / 2 + 8, tl.y + (br.y - tl.y) / 2 + 8},
			.color = 0x00FFFF,
			.fill = false,
		}
	});
}

void fractol_move(t_fractol *f)
{	
	if (ev_wheel_delta(&f->ui))
		move_viewport(f, (t_pos){0, 0}, f->ui.event.event.mouse.to, ev_wheel_delta(&f->ui));
	else if (f->ui.event.type == UI_MOUSE_MOVE && f->ui.mouse_down == MOUSE_LEFT)
	{
		move_viewport(f, f->ui.event.event.mouse.from,
				f->ui.event.event.mouse.to, 0);
	}
	move_reticle(f);
	if (!f->has_next_view && f->ui.event.type == UI_MOUSE_MOVE && f->ui.mouse_down == MOUSE_LEFT)
	{
		f->ui.img_pos.x += (f->ui.event.event.mouse.to.x - f->ui.event.event.mouse.from.x);
		f->ui.img_pos.y += (f->ui.event.event.mouse.to.y - f->ui.event.event.mouse.from.y);
	}
}
