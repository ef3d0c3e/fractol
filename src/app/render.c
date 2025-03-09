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
#include <app/fractol.h>
#include <app/viewport/viewport.h>
#include <kernel/post_processing.h>
#include <ui/event.h>

#include <ft_printf.h>
#include <mlx.h>
#include <mlx_int.h>

#include <sys/time.h>

void					upsampling_debug_fragment(t_img *buf, float *weights);
void					gradient_debug_fragment(t_img *buf,
							const t_gradient *gr);
void					render_keys(t_fractol *f);
struct s_fragment_data	init_data(
							t_fractol *f,
							float *oversampling_data,
							int downsampling);

/* Renders text by bypassing the draqueue */
static void	status(t_fractol *f, char *s)
{
	const int	x = f->ui.size.x * 0.05f;
	const int	y = 7 * f->ui.size.y / 8;

	mlx_string_put(f->mlx, f->window, x + 2, y + 2, 0x2f2f2f, s);
	f->mlx->do_flush = 1;
	mlx_string_put(f->mlx, f->window, x, y, 0xFFFFFF, s);
}

/* Render debug overlays */
static void	fractol_render_debug(t_fractol *f)
{
	struct s_fragment_data	data;

	if (f->needs_resample_debug)
	{
		status(f, "Resmampling debug...");
		f->needs_resample_debug = false;
		data = init_data(f, postprocess_edge_filter(f->ui.render,
					f->filter_buffer), 1);
		upsampling_debug_fragment(f->ui.render, data.oversampling_data);
	}
	else if (f->needs_gradient_debug)
	{
		status(f, "Gradient debug...");
		f->needs_gradient_debug = false;
		data = (struct s_fragment_data){&f->view, f->ui.size,
			f->kernel->default_color, f->ui.render, f->oversampling,
			postprocess_edge_filter(f->ui.render, f->filter_buffer), false};
		gradient_debug_fragment(f->ui.render, &f->kernel_settings.gradient);
	}
}

static void	fractol_render_default(t_fractol *f)
{
	struct s_fragment_data	data;

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
		data.oversampling_data = postprocess_upscale(f->ui.render,
				data.render_size, f->filter_buffer);
		data.render_size = f->ui.size;
		f->kernel->render(&data, &f->kernel_settings, f->max_iter);
	}
}

static void	fractol_render_upsampling(t_fractol *f)
{
	struct s_fragment_data	data;

	status(f, "Upsampling...");
	f->needs_resample = false;
	f->ui.img_pos = (t_vec2d){0, 0};
	data = init_data(f,
			postprocess_edge_filter(f->ui.render, f->filter_buffer), 1);
	f->kernel->render(&data, &f->kernel_settings, f->max_iter);
}

void	fractol_render(t_fractol *f)
{
	struct timeval			start;
	struct timeval			stop;

	render_keys(f);
	gettimeofday(&start, NULL);
	if (f->needs_render)
	{
		fractol_render_default(f);
		gettimeofday(&stop, NULL);
		ft_printf("[R]ender: %u us\n", (unsigned int)((stop.tv_sec
					- start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec));
	}
	else if (f->needs_resample)
	{
		fractol_render_upsampling(f);
		gettimeofday(&stop, NULL);
		ft_printf("[U]psample: %u us\n", (unsigned int)((stop.tv_sec
					- start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec));
	}
	fractol_render_debug(f);
}
