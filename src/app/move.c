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

#include <app/fractol.h>
#include <stdbool.h>

/* Moves or zoom the viewport */
static t_pos
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
			f->view.screen_to_space(view, (t_vec2d){start.x
				/ (double)f->ui.size.x, start.y / (double)f->ui.size.x}),
			f->view.screen_to_space(view, (t_vec2d){end.x
				/ (double)f->ui.size.x, end.y / (double)f->ui.size.x}),
			1.0);
	}
	if (zoom_delta)
	{
		if (!f->has_next_view)
			f->next_view = f->view;
		f->has_next_view = true;
		view_zoom(&f->next_view, f->view.screen_to_space(&f->view, (t_vec2d){
				end.x / (double)f->ui.size.x, end.y / (double)f->ui.size.y
			}), -zoom_delta);
	}
	return ((t_pos){end.x - start.x, end.y - start.y});
}

/* Displays reticles and move area */
static void	move_reticle(t_fractol *f)
{
	double	*data;
	t_pos	tl;
	t_pos	br;

	data = f->view.view.data;
	if (f->has_next_view)
		data = f->next_view.view.data;
	tl = f->view.space_to_screen(&f->view,
			(t_vec2d){data[0], data[3]});
	br = f->view.space_to_screen(&f->view,
			(t_vec2d){data[1], data[2]});
	(void)((br.x <= tl.x) && (tl.x ^= br.x, br.x ^= tl.x, tl.x ^= br.x));
	(void)((br.y <= tl.y) && (tl.y ^= br.y, br.y ^= tl.y, tl.y ^= br.y));
	drawqueue_push(&f->ui.ui_queue, (t_draw_item){
		.item = DRAW_RECT, .draw.rect = {.top_left = tl, .bottom_right = br,
		.color = 0x00FF00 + 0xFF * f->has_next_view, .fill = false}});
	drawqueue_push(&f->ui.ui_queue, (t_draw_item){
		.item = DRAW_RECT, .draw.rect = {.top_left = {tl.x + (br.x - tl.x)
		/ 2 - 8, tl.y + (br.y - tl.y) / 2 - 8}, .bottom_right = {tl.x
		+ (br.x - tl.x) / 2 + 8, tl.y + (br.y - tl.y) / 2 + 8},
		.color = 0x00FFFF, .fill = false}});
}

/* Moves the viewport from keyboard input */
static t_pos	move_keyboard(t_fractol *f)
{
	t_pos	d;
	bool	old;

	d = (t_pos){0, 0};
	if (ev_key_pressed(&f->ui, KEY_KP_PLUS))
		d = move_viewport(f, (t_pos){0, 0},
				(t_pos){f->ui.size.x / 2, f->ui.size.y / 2}, -1);
	else if (ev_key_pressed(&f->ui, KEY_KP_MINUS))
		d = move_viewport(f, (t_pos){0, 0},
				(t_pos){f->ui.size.x / 2, f->ui.size.y / 2}, 1);
	if (f->selector_shown)
		return (d);
	old = f->ui.force_redraw;
	f->ui.force_redraw = true;
	if (ev_key_pressed(&f->ui, KEY_ARROW_UP))
		d = move_viewport(f, (t_pos){0, 0}, (t_pos){0, 4}, 0);
	else if (ev_key_pressed(&f->ui, KEY_ARROW_DOWN))
		d = move_viewport(f, (t_pos){0, 0}, (t_pos){0, -4}, 0);
	else if (ev_key_pressed(&f->ui, KEY_ARROW_LEFT))
		d = move_viewport(f, (t_pos){0, 0}, (t_pos){4, 0}, 0);
	else if (ev_key_pressed(&f->ui, KEY_ARROW_RIGHT))
		d = move_viewport(f, (t_pos){0, 0}, (t_pos){-4, 0}, 0);
	else
		f->ui.force_redraw = old;
	return (d);
}

void	fractol_move(t_fractol *f)
{
	t_pos	d;

	d = (t_pos){0, 0};
	if (ev_wheel_delta(&f->ui))
		d = move_viewport(f, (t_pos){0, 0}, f->ui.event.event.mouse.to,
				ev_wheel_delta(&f->ui));
	else if (f->ui.event.type == UI_MOUSE_MOVE
		&& f->ui.mouse_down == MOUSE_LEFT)
		d = move_viewport(f, f->ui.event.event.mouse.from,
				f->ui.event.event.mouse.to, 0);
	else
		d = move_keyboard(f);
	move_reticle(f);
	(void)((!f->has_next_view) && (f->ui.img_pos.x += d.x,
				f->ui.img_pos.y += d.y));
}
