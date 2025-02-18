#include "ui.h"
#include "fractol.h"
#include "mlx.h"

t_pos	pos_new(int x, int y)
{
	return ((t_pos){
		.x = x,
		.y = y,
	});
}

t_ui	ui_init()
{
	return ((t_ui){
		.needs_render = true,
		.mouse_down = false,
		.img_pos = pos_new(0, 0),
		.mouse_pos = pos_new(0, 0),
		.mouse_delta = pos_new(0, 0)
	});
}

void ui_draw(t_fractol *f)
{
	if (f->ui.needs_render)
		f->kernel.render(&f->view, &f->img);
	mlx_put_image_to_window(f->mlx, f->window, f->img.img, f->ui.img_pos.x, f->ui.img_pos.y);
	f->ui.needs_render = false;
}
