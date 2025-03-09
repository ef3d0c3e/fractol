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

/**
 * @brief Mouse event handlers
 */

#include <app/fractol.h>

int	ev_mousedown(enum e_mousecode code, int x, int y, t_fractol *f)
{
	f->ui.event.type = UI_MOUSE_PRESS;
	f->ui.event.event.mouse.code = code;
	f->ui.event.event.mouse.to = (t_pos){x, y};
	f->ui.event.event.mouse.from = f->ui.mouse_pos;
	f->ui.mouse_pos = f->ui.event.event.mouse.to;
	if (code != MOUSE_WHEEL_DOWN && code != MOUSE_WHEEL_UP)
		f->ui.mouse_down = code;
	return (ui_update(f), 0);
}

int	ev_mouseup(enum e_mousecode code, int x, int y, t_fractol *f)
{
	f->ui.event.type = UI_MOUSE_RELEASE;
	f->ui.event.event.mouse.code = code;
	f->ui.event.event.mouse.to = (t_pos){x, y};
	f->ui.event.event.mouse.from = f->ui.mouse_pos;
	f->ui.mouse_pos = f->ui.event.event.mouse.to;
	if (code != MOUSE_WHEEL_DOWN && code != MOUSE_WHEEL_UP)
		f->ui.mouse_down = MOUSE_NONE;
	return (ui_update(f), 0);
}

int	ev_mousemove(int x, int y, t_fractol *f)
{
	f->ui.event.type = UI_MOUSE_MOVE;
	f->ui.event.event.mouse_move.to = (t_pos){x, y};
	f->ui.event.event.mouse_move.from = f->ui.mouse_pos;
	f->ui.mouse_pos = f->ui.event.event.mouse.to;
	return (ui_update(f), 0);
}
