/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Utilities for events
 */

#include <ui/event.h>
#include <ui/ui.h>

bool	ev_key_pressed(t_ui *ui, enum e_keycode code)
{
	return (ui->event.type == UI_KEY_RELEASE
		&& ui->event.event.keyboard.code == code);
}

bool	ev_key_held(t_ui *ui, enum e_keycode code)
{
	return (ui->event.type == UI_KEY_PRESS
		&& ui->event.event.keyboard.code == code);
}

bool	ev_mouse_pressed(t_ui *ui, enum e_mousecode code)
{
	return (ui->event.type == UI_MOUSE_RELEASE
		&& ui->event.event.mouse.code == code);
}

bool	ev_mouse_held(t_ui *ui, enum e_mousecode code)
{
	return (ui->event.type == UI_MOUSE_PRESS
		&& ui->event.event.mouse.code == code);
}

int	ev_wheel_delta(t_ui *ui)
{
	if (ui->event.type != UI_MOUSE_RELEASE)
		return (0);
	return (-(ui->event.event.mouse.code == MOUSE_WHEEL_DOWN)
		+(ui->event.event.mouse.code == MOUSE_WHEEL_UP));
}
