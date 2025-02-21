/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_keyboard.c                                   :+:      :+:    :+:   */
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

int	ev_keyup(enum e_keycode code, t_fractol *f)
{
	if (code == KEY_R)
	{
		f->ui.needs_render = true;
		f->ui.img_pos = pos_new(0, 0);
	}
	else if (code == KEY_S)
		f->ui.selector_shown = !f->ui.selector_shown;
	else if (code == KEY_U)
		f->ui.needs_resample = true;
	else
		return (0);
	return (ui_draw(f), 0);
}

int	ev_keydown(enum e_keycode code, t_fractol *f)
{
	if (code == KEY_ARROW_DOWN && f->ui.selector_shown)
		++f->ui.selector_id;
	else if (code == KEY_ARROW_UP && f->ui.selector_shown)
		--f->ui.selector_id;
	else
		return (0);
	return (ui_draw(f), 0);
}
