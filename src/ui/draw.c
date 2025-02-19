/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Drawing primitives
 */

#include "draw.h"
#include "mlx_int.h"
#include <X11/X.h>
#include <X11/Xlib.h>

static inline void	draw_rect(t_xvar *mlx, t_win_list *win, const struct s_draw_rect *rect)
{
	XGCValues	xgcv;

	xgcv.foreground = mlx_int_get_good_color(mlx, rect->color);
	if (rect->fill)
		xgcv.fill_style = FillSolid;
	XChangeGC(mlx->display, win->gc, GCForeground, &xgcv);
	XDrawRectangle(
		mlx->display, win->window, win->gc,
		rect->top_left.x,
		rect->top_left.y,
		rect->bottom_right.x - rect->top_left.x,
		rect->bottom_right.y - rect->top_left.y
	);
}

static inline void	draw_line(t_xvar *mlx, t_win_list *win, const struct s_draw_line *line)
{
	// TODO
}

static inline void	draw_circle(t_xvar *mlx, t_win_list *win, const struct s_draw_circle *circle)
{
	// TODO
}

inline void	draw(t_xvar *mlx, t_win_list *win, const t_draw_item *item)
{
	static void(*const drawer_table[])(t_xvar *mlx, t_win_list *win, const t_draw_item *item) = {
		[DRAW_RECT] = (void*)draw_rect,
		[DRAW_LINE] = (void*)draw_line,
		[DRAW_CIRCLE] = (void*)draw_circle,
	};

	drawer_table[item->rect.item](mlx, win, item);
}
