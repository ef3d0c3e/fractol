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

uint32_t	draw_hash(const t_draw_item *item, uint32_t seed);

t_drawqueue
	drawqueue_new(void)
{
	return ((t_drawqueue){
		.capacity = 0,
		.size = 0,
		.queue = NULL,
		.seed = 14547710,
		.hash = 0,
		.last_hash = 0,
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
	const uint32_t	hash = draw_hash(&item, d->seed);

	if (d->size == d->capacity)
	{
		d->capacity = (d->capacity + !d->capacity) << 1;
		d->queue = ft_realloc(d->queue,
				sizeof(t_draw_item) * d->size,
				sizeof(t_draw_item) * d->capacity);
	}
	d->hash ^= hash;
	d->hash *= 0xcc9e2d51;
	d->hash ^= (d->hash >> 15);
	d->queue[d->size++] = item;
}

void
	drawqueue_clear(t_drawqueue *d)
{
	d->last_hash = d->hash;
	d->hash = 0;
	d->size = 0;
}

void
	drawqueue_render(const t_drawqueue *d, t_xvar *mlx, t_win_list *win)
{
	size_t		i;

	i = 0;
	while (i < d->size)
	{
		draw(mlx, win, &d->queue[i]);
		++i;
	}
}
