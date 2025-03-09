/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Base implementation of viewport functionalities
 */

#include <app/viewport/viewport.h>

t_viewport
	viewport_create(
		t_pos size,
		t_vec2d(*screen_to_space)(const t_viewport *this, t_vec2d pos),
		t_pos(*space_to_screen)(const t_viewport *this, t_vec2d pos),
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
		const t_vec2d start,
		const t_vec2d end,
		const double factor)
{
	const t_vec2d	delta = {(start.x - end.x) * factor,
		(start.y - end.y) * factor};

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
	const double	factor = pow(0.9, zoom);
	const t_vec2d	new_size = {
		(this->view.data[1] - this->view.data[0]) * factor,
		(this->view.data[3] - this->view.data[2]) * factor,
	};

	this->view.data[0] = center.x - new_size.x / 2.0;
	this->view.data[1] = center.x + new_size.x / 2.0;
	this->view.data[2] = center.y - new_size.y / 2.0;
	this->view.data[3] = center.y + new_size.y / 2.0;
}
