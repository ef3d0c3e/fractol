/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "event.h"
#include <app/fractol.h>

void
move_event(
	t_fractol *fractol,
	const t_pos start,
	const t_pos end,
	const int zoom_delta
	);

int	ev_mousedown(enum e_mousecode code, int x, int y, t_fractol *f)
{
	if (code == MOUSE_WHEEL_UP)
		return (move_event(f, (t_pos){x, y}, (t_pos){0, 0}, -1), 0);
	else if (code == MOUSE_WHEEL_DOWN)
		return (move_event(f, (t_pos){x, y}, (t_pos){0, 0}, 1), 0);
	else if (code != MOUSE_LEFT)
		return (0);
	f->ui.mouse_pos.x = x;
	f->ui.mouse_pos.y = y;
	f->ui.mouse_down = true;
	return (0);
}

int	ev_mouseup(enum e_mousecode code, int x, int y, t_fractol *f)
{
	f->ui.mouse_down = false;
	return (0);
}

int	ev_mousemove(int x, int y, t_fractol *f)
{
	const t_pos	pos = {x, y};

	if (!f->ui.mouse_down)
		return (0);
	move_event(f, f->ui.mouse_pos, pos, 0);
	f->ui.mouse_delta.x = x - f->ui.mouse_pos.x;
	f->ui.mouse_delta.y = y - f->ui.mouse_pos.y;
	f->ui.mouse_pos = pos;
	f->ui.img_pos.x += f->ui.mouse_delta.x;
	f->ui.img_pos.y += f->ui.mouse_delta.y;
	ui_draw(f);
	return (0);
}
