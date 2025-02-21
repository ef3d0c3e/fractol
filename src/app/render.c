#include "fractol.h"
#include "mlx.h"
#include <kernel/post_processing.h>
#include <ui/event.h>

static void	status(t_fractol *f, char *s)
{
	const int	x = f->ui.size.x / 8;
	const int	y = f->ui.size.y / 5;
	XGCValues	xgcv;

	printf("%s\n", s);
	xgcv.foreground = 0xFFFFFF;
	XChangeGC(f->mlx->display, f->window->gc, GCForeground, &xgcv);
	XDrawString(
		f->mlx->display, f->window->window, f->window->gc,
		200, 200,
		s, strlen(s)
		);
}


void	fractol_render(t_fractol *f)
{
	struct s_fragment_data	data;

	if (ev_key_pressed(&f->ui, KEY_R))
		f->needs_render = true;
	else if (ev_key_pressed(&f->ui, KEY_U))
		f->needs_resample = true;

	if (f->needs_render)
	{
		status(f, "Rendering...");
		f->ui.img_pos = pos_new(0, 0);
		f->last_view = f->view;
		data = (struct s_fragment_data){
			.viewport = &f->view,
			.oversampling_data = NULL,
			.img = f->ui.render
		};
		f->kernel->render(&data, &f->kernel_settings, 500);
		f->needs_render = false;
	}
	else if (f->needs_resample)
	{
		status(f, "Upsampling...");
		data = (struct s_fragment_data){&f->view, f->ui.render,
			sobel(f->ui.render, f->filter_buffer)};
		f->kernel->render(&data, &f->kernel_settings, 500);
		f->needs_resample = false;
	}
}
