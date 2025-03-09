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

/**
 * @brief Keyboard event handlers
 */

#include <app/fractol.h>

int	ev_keyup(enum e_keycode code, t_fractol *f)
{
	f->ui.event.type = UI_KEY_RELEASE;
	f->ui.event.event.keyboard.code = code;
	return (ui_update(f), 0);
}

int	ev_keydown(enum e_keycode code, t_fractol *f)
{
	f->ui.event.type = UI_KEY_PRESS;
	f->ui.event.event.keyboard.code = code;
	return (ui_update(f), 0);
}
