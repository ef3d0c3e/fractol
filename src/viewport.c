#include "viewport.h"

struct s_viewport	viewport_create(size_t sz_x, size_t sz_y)
{
	return ((struct s_viewport) {
		.cx = 0.0,
		.cy = 0.0,
		.zoom = 400.0,
		.sz_x = sz_x,
		.sz_y = sz_y,
		.aa = 1,
	});
}

void viewport_foreach(
		const struct s_viewport *view,
		void (*callback)(const size_t x, const size_t y, const double zr, const double zi, void*),
		void *closure)
{
	size_t		pos[2];

	pos[1] = 0;
	while (pos[1] < view->sz_y)
	{
		pos[0] = 0;
		while (pos[0] < view->sz_x)
		{
			callback(
					pos[0],
					pos[1],
					((double)pos[0])/view->sz_x - 0.5 + view->cx,
					((double)pos[1])/view->sz_y + 0.5 + view->cy,
					closure
					);
			++pos[0];
		}
		++pos[1];
	}
}
