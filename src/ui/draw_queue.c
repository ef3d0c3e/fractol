#include "draw.h"
#include <util/util.h>

t_drawqueue
drawqueue_new()
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
	t_draw_item	*new;

	if (d->size == d->capacity)
	{
		d->capacity = (d->capacity + !d->capacity) << 1;
		d->queue = ft_realloc(d->queue, sizeof(t_draw_item) * d->size, sizeof(t_draw_item) * d->capacity);
	}
	d->queue[d->size++] = item;
}

void
drawqueue_clear(t_drawqueue *d)
{
	d->size = 0;
}

void
drawqueue_render(const t_drawqueue *d, t_img *img)
{
	size_t	i;

	i = 0;
	while (i < d->size)
	{
		draw(img, &d->queue[i]);
		++i;
	}
}
