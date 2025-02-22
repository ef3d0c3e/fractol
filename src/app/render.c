#include "fractol.h"
#include "mlx.h"
#include <X11/Xlib.h>
#include <kernel/post_processing.h>
#include <ui/event.h>

static void	status(t_fractol *f, char *s)
{
	const int	x = f->ui.size.x * 0.05f;
	const int	y = 7 * f->ui.size.y / 8;

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
		f->max_iter += 3;
	else if (ev_key_held(&f->ui, KEY_A))
		f->max_iter -= 3;
}


void	fractol_render(t_fractol *f)
{
	struct s_fragment_data	data;

	render_keys(f);
	if (f->needs_render)
	{
		status(f, "Rendering...");
		f->ui.img_pos = pos_new(0, 0);
		f->last_view = f->view;
		data = (struct s_fragment_data){
			.viewport = &f->view,
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
		data = (struct s_fragment_data){&f->view, f->ui.render,
			sobel(f->ui.render, f->filter_buffer), false};
		f->kernel->render(&data, &f->kernel_settings, f->max_iter);
		f->needs_resample = false;
	}
}
