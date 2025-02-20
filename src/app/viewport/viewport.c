#include "viewport.h"
#include "kernel/kernel.h"
#include "ui/image.h"
#include "util/vector.h"
#include <util/math.h>
#include <stdlib.h>

t_viewport
viewport_create(
		t_pos size,
		t_vec2d(*screen_to_space)(const t_viewport *this, const t_pos pos),
		t_pos(*space_to_screen)(const t_viewport *this, const t_vec2d pos),
		const void *data)
{
	return ((t_viewport){
		.size = size,
		.view = {{
			-(double)size.x / size.y,
			(double)size.x / size.y,
			-1.0,
			1.0
		}},
		.screen_to_space = screen_to_space,
		.space_to_screen = space_to_screen,
		.data = data,
	});
}

void
viewport_free(t_viewport *this)
{
	free((void *)this->data);
}

void
	view_move(
		t_viewport *this,
		const t_pos start,
		const t_pos end,
		const double factor)
{
	const t_vec2d	s = this->screen_to_space(this, start);
	const t_vec2d	e = this->screen_to_space(this, end);
	const t_vec2d	delta = {s.x - e.x, s.y - e.y};

	this->view.data[0] = (this->view.data[0] + delta.x * factor);
	this->view.data[1] = (this->view.data[1] + delta.x * factor);
	this->view.data[2] = (this->view.data[2] + delta.y * factor);
	this->view.data[3] = (this->view.data[3] + delta.y * factor);
}

void
	view_zoom(
	t_viewport *this,
	const t_vec2d center,
	const int zoom)
{
	const double	factor = pow(0.9, zoom);
	t_pos			old_c;
	t_vec2d			c;

	old_c = this->space_to_screen(this, (t_vec2d){
		(this->view.data[1] + this->view.data[0]) / 2.0,
		(this->view.data[3] + this->view.data[2]) / 2.0
	});
	view_move(this, this->space_to_screen(this, center), old_c, 1);
	c = (t_vec2d){
		(this->view.data[1] + this->view.data[0]) / 2.0,
		(this->view.data[3] + this->view.data[2]) / 2.0
	};
	this->view.data[0] = c.x - (c.x - this->view.data[0]) * factor;
	this->view.data[1] = c.x + (this->view.data[1] - c.x) * factor;
	this->view.data[2] = c.y - (c.y - this->view.data[2]) * factor;
	this->view.data[3] = c.y + (this->view.data[3] - c.y) * factor;
}

void
viewport_fragment(
		const t_viewport *this,
		t_img *img,
		t_color (*callback)(t_pos pos, t_vec2d z, void *data),
		void *closure)
{
	char *shared = img->data;

#pragma omp parallel shared(shared)
	{
		int y;
#pragma omp for private(y) schedule(dynamic)
		for (y = 0; y < this->size.y; ++y)
		{
			for (int x = 0; x < this->size.x; ++x)
			{	
				const t_color color =
					callback((t_pos){x, y}, this->screen_to_space(this, (t_pos){x, y}), closure);
				image_pixel(img, (t_pos){x, y}, color);
			}
		}
	}
}
