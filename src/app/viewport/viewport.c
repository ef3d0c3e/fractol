#include "viewport.h"
#include "matrix.h"
#include "ui.h"
#include "vector.h"
#include <math.h>

t_viewport
viewport_create(
		t_pos size,
		t_vec2d(*screen_to_space)(const t_viewport *this, const t_pos pos),
		t_pos(*space_to_screen)(const t_viewport *this, const t_vec2d pos),
		const void *data)
{
	return ((t_viewport){
		.size = size,
		.view = { { -2.0, 1.0, -1.0, 1.0 } }, // TODO: Aspect ratio
		.screen_to_space = screen_to_space,
		.space_to_screen = space_to_screen,
		.data = data,
	});
}

void
view_move(
		t_viewport *this,
		const t_pos start,
		const t_pos end,
		const int zoom_delta)
{
	const t_vec2d s = this->screen_to_space(this, start);
	const t_vec2d e = this->screen_to_space(this, end);
	const t_vec2d delta = {
		s.x - e.x,
		s.y - e.y,
	};
	this->view.data[0] = (this->view.data[0] + delta.x) * pow(0.9, zoom_delta);
	this->view.data[1] = (this->view.data[1] + delta.x) * pow(0.9, zoom_delta);
	this->view.data[2] = (this->view.data[2] + delta.y) * pow(0.9, zoom_delta);
	this->view.data[3] = (this->view.data[3] + delta.y) * pow(0.9, zoom_delta);
}

void
viewport_foreach(
		const t_viewport *this,
		void (*callback)(t_pos pos, t_vec2d z, void *data),
		void *closure)
{
	t_pos	pos;

	pos.y = 0;
	while (pos.y < this->size.y)
	{
		pos.x = 0;
		while (pos.x < this->size.x)
		{	
			callback(pos, this->screen_to_space(this, pos), closure);
			++pos.x;
		}
		++pos.y;
	}
}
