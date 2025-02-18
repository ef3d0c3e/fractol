#include "kernel.h"

uint8_t	*kernel_resize_buffer(uint8_t *buffer, t_viewport *view)
{
	size_t	sz;
	uint8_t	*new;

	if (buffer)
	{
		sz = ((size_t *)buffer)[0];
		if (sz >= view->size.x * view->size.y * 4)
			return (buffer);
		free(buffer);
	}
	sz = view->size.x * view->size.y * 4;
	buffer = malloc(sizeof(size_t) + sz);
	((size_t *)buffer)[0] = sz;
	return (buffer + sizeof(size_t));
}
