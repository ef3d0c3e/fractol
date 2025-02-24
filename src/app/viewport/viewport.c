#include "viewport.h"
#include "kernel/kernel.h"
#include "ui/image.h"
#include "util/vector.h"
#include <util/math.h>
#include <stdlib.h>

t_viewport
viewport_create(
		t_pos size,
		t_vec2d(*screen_to_space)(const t_viewport *this, const t_pos pos, const t_vec2d delta),
		t_pos(*space_to_screen)(const t_viewport *this, const t_vec2d pos),
		void *data)
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
	/*
	const t_vec2d	s = this->screen_to_space(this, start, (t_vec2d){0, 0});
	const t_vec2d	e = this->screen_to_space(this, end, (t_vec2d){0, 0});
	//const t_vec2d	s = {
	//	(this->view.data[0] + (((double)start.x) / this->size.x)
	//		* (this->view.data[1] - this->view.data[0])),
	//	(this->view.data[2] + (((double)start.y) / this->size.y)
	//	 	* (this->view.data[3] - this->view.data[2]))
	//};
	//const t_vec2d	e = {
	//	(this->view.data[0] + (((double)end.x) / this->size.x)
	//		* (this->view.data[1] - this->view.data[0])),
	//	(this->view.data[2] + (((double)end.y) / this->size.y)
	//	 	* (this->view.data[3] - this->view.data[2]))
	//};
	const t_vec2d	delta = {s.x - e.x, s.y - e.y};

	this->view.data[0] = (this->view.data[0] + delta.x * factor);
	this->view.data[1] = (this->view.data[1] + delta.x * factor);
	this->view.data[2] = (this->view.data[2] + delta.y * factor);
	this->view.data[3] = (this->view.data[3] + delta.y * factor);*/
	const t_vec2d s = this->screen_to_space(this, start, (t_vec2d){0, 0});
	const t_vec2d e = this->screen_to_space(this, end, (t_vec2d){0, 0});
	const t_vec2d delta = {(s.x - e.x) * factor, (s.y - e.y) * factor};

	this->view.data[0] += delta.x;
	this->view.data[1] += delta.x;
	this->view.data[2] += delta.y;
	this->view.data[3] += delta.y;
}

void
	view_zoom(
	t_viewport *this,
	const t_vec2d center,
	const int zoom)
{
	/*
	const double	factor = pow(0.9, zoom);
	const t_pos		screen_center = {this->size.x / 2, this->size.y / 2};
	t_vec2d			c;

	t_pos ss = this->space_to_screen(this, center);
	view_move(this, ss, screen_center, 1);
	c = (t_vec2d){
		(this->view.data[1] + this->view.data[0]) / 2.0,
		(this->view.data[3] + this->view.data[2]) / 2.0
	};
	this->view.data[0] = c.x - (c.x - this->view.data[0]) * factor;
	this->view.data[1] = c.x + (this->view.data[1] - c.x) * factor;
	this->view.data[2] = c.y - (c.y - this->view.data[2]) * factor;
	this->view.data[3] = c.y + (this->view.data[3] - c.y) * factor;
	*/	
	const double factor = pow(0.9, zoom);
	t_vec2d new_size;
	t_vec2d delta;

	// Compute new viewport size
	new_size.x = (this->view.data[1] - this->view.data[0]) * factor;
	new_size.y = (this->view.data[3] - this->view.data[2]) * factor;

	// Compute new viewport bounds centered around `center`
	delta.x = center.x - (this->view.data[0] + this->view.data[1]) / 2.0;
	delta.y = center.y - (this->view.data[2] + this->view.data[3]) / 2.0;

	this->view.data[0] = center.x - new_size.x / 2.0 + delta.x * (1.0 - factor);
	this->view.data[1] = center.x + new_size.x / 2.0 + delta.x * (1.0 - factor);
	this->view.data[2] = center.y - new_size.y / 2.0 + delta.y * (1.0 - factor);
	this->view.data[3] = center.y + new_size.y / 2.0 + delta.y * (1.0 - factor);
}
