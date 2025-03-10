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
 * @file Drawing primitives using pure MLX
 */

#include "mlx.h"
#include "mlx_int.h"
#include <ui/draw.h>

/* Draws a filled rectangle */
static inline void
	rect_fill(t_xvar *mlx, t_win_list *win, const struct s_draw_rect *rect)
{
	int	i;
	int	j;

	i = rect->top_left.x;
	while (i <= rect->bottom_right.x)
	{
		j = rect->top_left.y;
		while (j <= rect->bottom_right.y)
		{
			mlx_pixel_put(mlx, win, i, j, rect->color);
			++j;
		}
		++i;
	}
}

/* Draws a rectangle */
static inline void
	draw_rect(
		t_xvar *mlx,
		t_win_list *win,
		const struct s_draw_rect *rect
		)
{
	int	i;

	if (rect->fill)
	{
		rect_fill(mlx, win, rect);
		return ;
	}
	i = rect->top_left.x;
	while (i <= rect->bottom_right.x)
	{
		mlx_pixel_put(mlx, win, i, rect->top_left.y, rect->color);
		mlx_pixel_put(mlx, win, i, rect->bottom_right.y, rect->color);
		++i;
	}
	i = rect->top_left.y;
	while (i <= rect->bottom_right.y)
	{
		mlx_pixel_put(mlx, win, rect->top_left.x, i, rect->color);
		mlx_pixel_put(mlx, win, rect->bottom_right.x, i, rect->color);
		++i;
	}
}

/* Draws text */
static inline void
	draw_text(
		t_xvar *mlx,
		t_win_list *win,
		const struct s_draw_text *text
		)
{
	mlx_string_put(mlx, win, text->pos.x, text->pos.y, text->color,
		(char *)text->str);
}

/* Draws text with shadow */
static inline void
	draw_text_shadow(
		t_xvar *mlx,
		t_win_list *win,
		const struct s_draw_text_shadow *text
		)
{
	mlx_string_put(mlx, win, text->pos.x + 1, text->pos.y + 1, text->shadow,
		(char *)text->str);
	mlx_string_put(mlx, win, text->pos.x, text->pos.y, text->color,
		(char *)text->str);
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
