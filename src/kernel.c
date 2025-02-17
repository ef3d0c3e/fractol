#include "kernel.h"

uint8_t	*kernel_resize_buffer(uint8_t *buffer, t_viewport *view)
{
	size_t	sz;
	uint8_t	*new;

	if (buffer)
	{
		sz = ((size_t *)buffer)[0];
		if (sz >= view->sz_x * view->sz_y * view->aa * view->aa * 4)
			return (buffer);
		free(buffer);
	}
	sz = view->sz_x * view->sz_y * view->aa * view->aa * 4;
	buffer = malloc(sizeof(size_t) + sz);
	((size_t *)buffer)[0] = sz;
	return (buffer + sizeof(size_t));
}
