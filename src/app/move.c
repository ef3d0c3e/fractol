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
 * @file Handles camera movements
 */

#include "fractol.h"
#include "ui/event.h"

void
	move_viewport(
	t_fractol *f,
	const t_pos start,
	const t_pos end,
	const int zoom_delta
	)
{
	if (!zoom_delta)
		view_move(&f->view, start, end, 1.0);
	else
		view_zoom(&f->view, f->last_view.screen_to_space(&f->last_view, end, (t_vec2d){0, 0}), -zoom_delta);
}

/* Displays reticles and move area */
static double	move_reticle(t_fractol *f)
{
	const t_pos tl = f->last_view.space_to_screen(&f->last_view,
			(t_vec2d){f->view.view.data[0], f->view.view.data[2]});
	const t_pos br = f->last_view.space_to_screen(&f->last_view,
			(t_vec2d){f->view.view.data[1], f->view.view.data[3]});

	// Render rectangle
	drawqueue_push(&f->ui.ui_queue, (t_draw_item){
		.item = DRAW_RECT,
		.draw.rect = {
			.top_left = tl,
			.bottom_right = br,
			.color = 0x00FF00,
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
	return ((f->view.view.data[1] - f->view.view.data[0]) / (f->last_view.view.data[1] - f->last_view.view.data[0]));
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
	double r = move_reticle(f);
	if (f->ui.event.type == UI_MOUSE_MOVE && f->ui.mouse_down == MOUSE_LEFT)
	{
		f->ui.img_pos.x += r * (f->ui.event.event.mouse.to.x - f->ui.event.event.mouse.from.x);
		f->ui.img_pos.y += r * (f->ui.event.event.mouse.to.y - f->ui.event.event.mouse.from.y);
	}
}
