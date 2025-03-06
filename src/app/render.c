#include "fractol.h"
#include "kernel/color.h"
#include "kernel/gradient.h"
#include "mlx.h"
#include <X11/Xlib.h>
#include <kernel/post_processing.h>
#include <ui/event.h>

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
	else if (ev_key_held(&f->ui, KEY_Q))
		f->max_iter = min(20000, f->max_iter + 3);
	else if (ev_key_held(&f->ui, KEY_A))
		f->max_iter = max(1, f->max_iter - 3);
}


void	fractol_render(t_fractol *f)
{
	struct s_fragment_data	data;

	data.dafault_color = f->kernel->default_color;
	render_keys(f);
	if (f->needs_render)
	{
		status(f, "Rendering...");
		f->ui.img_pos = (t_vec2d){0, 0};
		if (f->has_next_view)
			f->view = f->next_view;
		f->has_next_view = false;
		data = (struct s_fragment_data){
			.viewport = &f->view,
			.dafault_color = f->kernel->default_color,
			.oversampling_data = NULL,
			.img = f->ui.render,
			.post_pass = f->post_pass,
		};
		f->kernel->render(&data, &f->kernel_settings, f->max_iter);
		f->needs_render = false;
		f->post_pass = false;
	}
	else if (f->needs_resample)
	{
		status(f, "Upsampling...");
		data = (struct s_fragment_data){&f->view,  f->kernel->default_color,
			f->ui.render,
			postprocess_edge_filter(f->ui.render, f->filter_buffer), false};
		f->kernel->render(&data, &f->kernel_settings, f->max_iter);
		f->needs_resample = false;
	}
	else if (f->needs_resample_debug)
	{
		status(f, "Resmampling debug...");
		data = (struct s_fragment_data){&f->view,  f->kernel->default_color,
			f->ui.render,
			postprocess_edge_filter(f->ui.render, f->filter_buffer), false};
		for (int i = 0; i < f->ui.render->width * f->ui.render->height; ++i)
			((t_color *)f->ui.render->data)[i] = color_lerp((t_color){0x000000}, (t_color){0xFFFFFF}, exp(-data.oversampling_data[i] / 4));
		f->needs_resample_debug = false;
	}
	else if (f->needs_gradient_debug)
	{
		status(f, "Gradient debug...");
		data = (struct s_fragment_data){&f->view,  f->kernel->default_color,
			f->ui.render,
			postprocess_edge_filter(f->ui.render, f->filter_buffer), false};
		for (int i = 0; i < f->ui.render->width; ++i)
		{
			for (int j = f->ui.render->height / 10 * 9; j < f->ui.render->height; ++j)
				((t_color *)f->ui.render->data)[i + j * f->ui.render->width] = gradient_get(&f->kernel_settings.gradient, ((float)i) / f->ui.render->width);
		}
		f->needs_gradient_debug = false;
	}
}
