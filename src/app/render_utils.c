/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <app/fractol.h>
#include <kernel/color.h>
#include <util/pos.h>
#include <kernel/gradient.h>
#include <mlx_int.h>
#include <math.h>

/* Render upsampling data as grayscale image */
void	upsampling_debug_fragment(t_img *buf, float *weights)
{
	const size_t	size = buf->width * (size_t)buf->height;
	t_color			*data;
	size_t			i;

	data = (t_color *)buf->data;
	i = 0;
	while (i < size)
	{
		data[i] = color_lerp((t_color){0x000000}, (t_color){0xFFFFFF},
				expf(-weights[i] / 4));
		++i;
	}
}

/* Render gradient overlay */
void	gradient_debug_fragment(t_img *buf, const t_gradient *gr)
{
	t_color	*data;
	t_color	color;
	t_pos	pos;

	data = (t_color *)buf->data;
	pos.x = 0;
	while (pos.x < buf->width)
	{
		pos.y = buf->height * 9 / 10;
		color = gradient_get(gr, pos.x / (float)buf->width);
		while (pos.y < buf->height)
		{
			data[pos.x + pos.y * buf->width] = color;
			++pos.y;
		}
		++pos.x;
	}
}

/* Handles render keybinds */
void	render_keys(t_fractol *f)
{
	if (ev_key_pressed(&f->ui, KEY_R))
		f->needs_render = true;
	else if (ev_key_pressed(&f->ui, KEY_T))
	{
		f->needs_render = true;
		f->post_pass = true;
	}
	else if (ev_key_pressed(&f->ui, KEY_U))
		f->needs_resample = true;
}

/* Initializes fragment data */
struct s_fragment_data	init_data(
	t_fractol *f,
	float *oversampling_data,
	int downsampling)
{
	return ((struct s_fragment_data){
		.viewport = &f->view,
		.render_size = {f->ui.size.x / downsampling,
			f->ui.size.y / downsampling},
		.dafault_color = f->kernel->default_color,
		.img = f->ui.render,
		.oversampling_factor = f->oversampling,
		.oversampling_data = oversampling_data,
		.post_pass = f->post_pass,
	});
}
