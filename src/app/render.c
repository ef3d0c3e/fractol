/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "app/viewport/viewport.h"
#include "fractol.h"
#include "kernel/color.h"
#include "kernel/gradient.h"
#include "mlx.h"
#include "mlx_int.h"
#include <X11/Xlib.h>
#include <kernel/post_processing.h>
#include <string.h>
#include <ui/event.h>
#include <sys/time.h>

/* Renders text by bypassing the draqueue */
static void	status(t_fractol *f, char *s)
{
	const int	x = f->ui.size.x * 0.05f;
	const int	y = 7 * f->ui.size.y / 8;

	mlx_string_put(f->mlx, f->window, x + 2, y + 2, 0x2f2f2f, s);
	f->mlx->do_flush = 1;
	mlx_string_put(f->mlx, f->window, x, y, 0xFFFFFF, s);
}

static void	render_keys(t_fractol *f)
{
	if (ev_key_pressed(&f->ui, KEY_R))
		f->needs_render = true;
	else if (ev_key_pressed(&f->ui, KEY_T))
		(f->needs_render = true, f->post_pass = true);
	else if (ev_key_pressed(&f->ui, KEY_U))
		f->needs_resample = true;
}

static struct s_fragment_data init_data(t_fractol *f, float *oversampling_data, int downsampling)
{
	return ((struct s_fragment_data){
		.viewport = &f->view,
		.render_size = {f->ui.size.x / downsampling, f->ui.size.y / downsampling},
		.dafault_color = f->kernel->default_color,
		.img = f->ui.render,
		.oversampling_factor = f->oversampling,
		.oversampling_data = oversampling_data,
		.post_pass = f->post_pass,
	});
}


void	fractol_render(t_fractol *f)
{
	struct s_fragment_data	data;

	data.dafault_color = f->kernel->default_color;
	render_keys(f);
	struct timeval stop, start;
	gettimeofday(&start, NULL);
	if (f->needs_render)
	{
		status(f, "Rendering...");
		if (f->has_next_view)
			f->view = f->next_view;
		f->has_next_view = false;
		f->needs_render = false;
		f->post_pass = false;
		f->ui.img_pos = (t_vec2d){0, 0};
		data = init_data(f, NULL, f->downsampling);
		f->kernel->render(&data, &f->kernel_settings, f->max_iter);
		if (f->downsampling != 1)
		{
			data.oversampling_data = postprocess_upscale(f->ui.render, data.render_size, f->filter_buffer);
			data.render_size = f->ui.size;
			f->kernel->render(&data, &f->kernel_settings, f->max_iter);
		}
		gettimeofday(&stop, NULL);
		printf("[R]ender: %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
	}
	else if (f->needs_resample)
	{
		status(f, "Upsampling...");
		f->needs_resample = false;
	f->ui.img_pos = (t_vec2d){0, 0};
		data = init_data(f, postprocess_edge_filter(f->ui.render, f->filter_buffer), 1);
		f->kernel->render(&data, &f->kernel_settings, f->max_iter);
		gettimeofday(&stop, NULL);
		printf("[U]psample: %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
	}
	else if (f->needs_resample_debug)
	{
		status(f, "Resmampling debug...");
		f->needs_resample_debug = false;
		data = init_data(f, postprocess_edge_filter(f->ui.render, f->filter_buffer), 1);
		for (int i = 0; i < f->ui.render->width * f->ui.render->height; ++i)
			((t_color *)f->ui.render->data)[i] = color_lerp((t_color){0x000000}, (t_color){0xFFFFFF}, exp(-data.oversampling_data[i] / 4));
	}
	else if (f->needs_gradient_debug)
	{
		status(f, "Gradient debug...");
		f->needs_gradient_debug = false;
		data = (struct s_fragment_data){&f->view, f->ui.size, f->kernel->default_color,
			f->ui.render,
			f->oversampling,
			postprocess_edge_filter(f->ui.render, f->filter_buffer), false};
		for (int i = 0; i < f->ui.render->width; ++i)
		{
			for (int j = f->ui.render->height / 10 * 9; j < f->ui.render->height; ++j)
				((t_color *)f->ui.render->data)[i + j * f->ui.render->width] = gradient_get(&f->kernel_settings.gradient, ((float)i) / f->ui.render->width);
		}
	}
}
