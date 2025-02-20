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

static inline void
	draw_rect(
		t_xvar *mlx,
		t_win_list *win,
		const struct s_draw_rect *rect
		)
{
	XGCValues	xgcv;

	xgcv.foreground = rect->color;
	XChangeGC(mlx->display, win->gc, GCForeground, &xgcv);
	if (rect->fill)
		XFillRectangle(
			mlx->display, win->window, win->gc,
			rect->top_left.x,
			rect->top_left.y,
			rect->bottom_right.x - rect->top_left.x,
			rect->bottom_right.y - rect->top_left.y
			);
	else
		XDrawRectangle(
			mlx->display, win->window, win->gc,
			rect->top_left.x,
			rect->top_left.y,
			rect->bottom_right.x - rect->top_left.x,
			rect->bottom_right.y - rect->top_left.y
			);
}

static inline void
	draw_line(
		t_xvar *mlx,
		t_win_list *win,
		const struct s_draw_line *line
		)
{
	XGCValues	xgcv;

	xgcv.foreground = line->color;
	xgcv.line_width = line->width;
	XChangeGC(mlx->display, win->gc, GCForeground, &xgcv);
	XDrawLine(
		mlx->display, win->window, win->gc,
		line->start.x,
		line->start.y,
		line->end.x,
		line->end.y
		);
}

static inline void
	draw_text(
		t_xvar *mlx,
		t_win_list *win,
		const struct s_draw_text *text
		)
{
	XGCValues	xgcv;

	xgcv.foreground = text->color;
	XChangeGC(mlx->display, win->gc, GCForeground, &xgcv);
	XDrawString(
		mlx->display, win->window, win->gc,
		text->pos.x,
		text->pos.y,
		text->str, strlen(text->str)
		);
}

inline void	draw(t_xvar *mlx, t_win_list *win, const t_draw_item *item)
{
	static	void (*const drawer_table[])
		(t_xvar *mlx, t_win_list *win, const t_draw_item *item) = {
	[DRAW_RECT] = (void*)draw_rect,
	[DRAW_LINE] = (void*)draw_line,
	[DRAW_TEXT] = (void*)draw_text,
	};

	drawer_table[item->rect.item](mlx, win, item);
}
