#include "viewport.h"

struct s_viewport	viewport_create(int sz_x, int sz_y)
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
		void (*callback)(int x, int y, double zr, double zi, void*),
		void *closure)
{
	int		pos[2];

	pos[0] = 0;
	while (pos[0] < view->sz_y)
	{
		pos[1] = 0;
		while (pos[1] < view->sz_x)
		{
			callback(
					pos[1],
					pos[0],
					((double)pos[1])/view->sz_x -  + view->cx,
					closure
					);
			++pos[1];
		}
		++pos[0];
	}
}
