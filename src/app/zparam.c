/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zparam.c                                             :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "app/fractol.h"
#include "util/pos.h"
#include "util/vector.h"
#include <complex.h>

/* Moves the Z parameter to the right-clicked location */
static void move_zparam(t_fractol *f)
{
	const t_vec2d	z = f->view.screen_to_space(&f->view,
		(t_vec2d){f->ui.mouse_pos.x / (double)f->ui.size.x,
		f->ui.mouse_pos.y / (double)f->ui.size.y});
	f->kernel_settings.zparam = z.x + I * z.y;
}

void	fractol_zparam(t_fractol *f)
{
	t_pos	center;

	if (f->ui.event.type == UI_MOUSE_PRESS && f->ui.mouse_down == MOUSE_RIGHT)
		move_zparam(f);
	center = f->view.space_to_screen(&f->view,
		(t_vec2d){creal(f->kernel_settings.zparam), cimag(f->kernel_settings.zparam)});
	if (center.x < 0 || center.x >= f->ui.size.x || center.y < 0 || center.y >=
		f->ui.size.y)
		return ;
	drawqueue_push(&f->ui.ui_queue, (t_draw_item){
		.item = DRAW_RECT,
		.draw.rect = {
			.top_left = {center.x - 4, center.y - 4},
			.bottom_right = {center.x + 4, center.y + 4},
			.color = 0xFFFF00,
			.fill = false,
		}
	});
}
