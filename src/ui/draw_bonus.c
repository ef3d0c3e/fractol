/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Drawing primitives using XLib
 */

#include <ui/draw.h>

#include <mlx_int.h>
#include <X11/X.h>
#include <X11/Xlib.h>

/* Draws a rectangle */
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

/* Draws text */
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

/* Draws text with shadow */
static inline void
	draw_text_shadow(
		t_xvar *mlx,
		t_win_list *win,
		const struct s_draw_text_shadow *text
		)
{
	XGCValues	xgcv;

	xgcv.foreground = text->shadow;
	XChangeGC(mlx->display, win->gc, GCForeground, &xgcv);
	XDrawString(
		mlx->display, win->window, win->gc,
		text->pos.x + 1,
		text->pos.y + 1,
		text->str, strlen(text->str)
		);
	xgcv.foreground = text->color;
	XChangeGC(mlx->display, win->gc, GCForeground, &xgcv);
	XDrawString(
		mlx->display, win->window, win->gc,
		text->pos.x,
		text->pos.y,
		text->str, strlen(text->str)
		);
}

void	draw(t_xvar *mlx, t_win_list *win, const t_draw_item *item)
{
	static	void (*const drawer_table[])
		(t_xvar *mlx, t_win_list *win, const t_draw_item *item) = {
	[DRAW_RECT] = (t_draw_fn)draw_rect,
	[DRAW_TEXT] = (t_draw_fn)draw_text,
	[DRAW_TEXT_SHADOW] = (t_draw_fn)draw_text_shadow,
	};

	drawer_table[item->item](mlx, win, (void *)&item->draw);
}
