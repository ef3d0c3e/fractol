/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef DRAW_H
# define DRAW_H

/**
 * @file Ui drawing
 */

# include "mlx_int.h"
# include "util/pos.h"
# include <stdint.h>
# include <stdbool.h>

/**
 * @brief Drawable primitives
 */
enum	e_draw_item
{
	DRAW_RECT,
	DRAW_LINE,
	DRAW_TEXT,
};

/**
 * @brief Drawable item data
 */
typedef struct s_draw_item
{
	enum e_draw_item	item;
	union u_draw_item
	{
		struct s_draw_rect
		{
			uint32_t			color;
			t_pos				top_left;
			t_pos				bottom_right;
			bool				fill;
		} rect;
		struct s_draw_line
		{
			uint32_t			color;
			t_pos				start;
			t_pos				end;
			int					width;
		} line;
		struct s_draw_text
		{
			uint32_t			color;
			t_pos				pos;
			const char			*str;
		} text;
	} draw;
}	t_draw_item;

/**
 * @brief Draw item to screen
 *
 * @param mlx X11 Handle
 * @param win Drawable
 * @param item Item to draw
 */
void
draw(t_xvar *mlx, t_win_list *win, const t_draw_item *item);

/**
 * @brief The draw queue
 */
typedef struct s_drawqueue
{
	size_t		capacity;
	size_t		size;
	t_draw_item	*queue;
}	t_drawqueue;

/**
 * @brief Creates a new draw queue
 */
t_drawqueue
drawqueue_new(void);

/**
 * @brief Frees the draw queue
 */
void
drawqueue_free(t_drawqueue *d);

/**
 * @brief Add an element to the draw queue
 */
void
drawqueue_push(t_drawqueue *d, const t_draw_item item);

/**
 * @brief Clears the draw queue
 */
void
drawqueue_clear(t_drawqueue *d);

/**
 * @brief Renders to screen
 */
void
drawqueue_render(const t_drawqueue *d, t_xvar *mlx, t_win_list *win);

#endif // DRAW_H
