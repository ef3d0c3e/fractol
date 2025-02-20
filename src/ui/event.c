/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <ui/event.h>
#include <app/fractol.h>
#include <mlx.h>

int	ev_keyup(enum e_keycode code, t_fractol *f);
int	ev_keydown(enum e_keycode code, t_fractol *f);

int	ev_mousedown(enum e_mousecode code, int x, int y, t_fractol *f);
int	ev_mouseup(enum e_mousecode code, int x, int y, t_fractol *f);
int	ev_mousemove(int x, int y, t_fractol *f);

void
	move_event(
	t_fractol *f,
	const t_pos start,
	const t_pos end,
	const int zoom_delta
	)
{
	if (!zoom_delta)
		view_move(&f->view, start, end, 1.0);
	else
		view_zoom(&f->view, f->last_view.screen_to_space(&f->last_view, start), zoom_delta);

	const t_pos tl = f->last_view.space_to_screen(&f->last_view,
			(t_vec2d){f->view.view.data[0], f->view.view.data[2]});
	const t_pos br = f->last_view.space_to_screen(&f->last_view,
			(t_vec2d){f->view.view.data[1], f->view.view.data[3]});

	// Render rectangle
	drawqueue_push(&f->ui.ui_queue, (t_draw_item){
		.item = DRAW_RECT,
		.draw.rect = {
			.fill = false,
			.color = 0x00FF00,
			.top_left = tl,
			.bottom_right = br,
		}
	});

	// Render reticle
	drawqueue_push(&f->ui.ui_queue, (t_draw_item){
		.item = DRAW_RECT,
		.draw.rect = {
			.fill = false,
			.color = 0x00FFFF,
			.top_left = {tl.x + (br.x - tl.x) / 2 - 8, tl.y + (br.y - tl.y) / 2 - 8},
			.bottom_right = {tl.x + (br.x - tl.x) / 2 + 8, tl.y + (br.y - tl.y) / 2 + 8},
		}
	});

	ui_draw(f);
}

void	event_setup(t_fractol *f)
{
	mlx_hook(f->window, EVENT_MOUSEDOWN, MASK_BUTTON_PRESS, ev_mousedown, f);
	mlx_hook(f->window, EVENT_MOUSEUP, MASK_BUTTON_RELEASE, ev_mouseup, f);
	mlx_hook(f->window, EVENT_MOUSEMOVE, MASK_POINTER_MOTION, ev_mousemove, f);
	mlx_hook(f->window, EVENT_KEYDOWN, MASK_KEY_PRESS, ev_keydown, f);
	mlx_hook(f->window, EVENT_KEYUP, MASK_KEY_RELEASE, ev_keyup, f);
	mlx_hook(f->window, EVENT_DESTROY, MASK_NONE, mlx_loop_end, f->mlx);
}
