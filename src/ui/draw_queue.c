/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Drawqueue buffer management
 */

#include <ui/draw.h>

#include <mlx_int.h>
#include <util/util.h>

t_drawqueue
	drawqueue_new(void)
{
	return ((t_drawqueue){
		.capacity = 0,
		.size = 0,
		.queue = 0,
	});
}

void
	drawqueue_free(t_drawqueue *d)
{
	free(d->queue);
}

void
	drawqueue_push(t_drawqueue *d, const t_draw_item item)
{
	if (d->size == d->capacity)
	{
		d->capacity = (d->capacity + !d->capacity) << 1;
		d->queue = ft_realloc(d->queue,
				sizeof(t_draw_item) * d->size,
				sizeof(t_draw_item) * d->capacity);
	}
	d->queue[d->size++] = item;
}

void
	drawqueue_clear(t_drawqueue *d)
{
	d->size = 0;
}

void
	drawqueue_render(const t_drawqueue *d, t_xvar *mlx, t_win_list *win)
{
	size_t	i;

	i = 0;
	while (i < d->size)
	{
		draw(mlx, win, &d->queue[i]);
		++i;
	}
}
