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
#include "ui/ui.h"
#include <ui/event.h>
#include <app/fractol.h>
#include <mlx.h>

int	ev_keyup(enum e_keycode code, t_fractol *f);
int	ev_keydown(enum e_keycode code, t_fractol *f);

int	ev_mousedown(enum e_mousecode code, int x, int y, t_fractol *f);
int	ev_mouseup(enum e_mousecode code, int x, int y, t_fractol *f);
int	ev_mousemove(int x, int y, t_fractol *f);

int	ev_resize(int width, int height, t_fractol *f);

void	event_setup(t_fractol *f)
{
	mlx_hook(f->window, EVENT_MOUSEDOWN, MASK_BUTTON_PRESS, ev_mousedown, f);
	mlx_hook(f->window, EVENT_MOUSEUP, MASK_BUTTON_RELEASE, ev_mouseup, f);
	mlx_hook(f->window, EVENT_MOUSEMOVE, MASK_POINTER_MOTION, ev_mousemove, f);
	mlx_hook(f->window, EVENT_KEYDOWN, MASK_KEY_PRESS, ev_keydown, f);
	mlx_hook(f->window, EVENT_KEYUP, MASK_KEY_RELEASE, ev_keyup, f);
	mlx_hook(f->window, EVENT_RESIZE, MASK_EnterWindowMask, ev_resize, f);
	mlx_hook(f->window, EVENT_DESTROY, MASK_NONE, mlx_loop_end, f->mlx);
}
