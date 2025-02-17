#include "../minilibx-linux/mlx.h"
#include "kernel.h"
#include "viewport.h"
#include "fractol.h"
#include "controls.h"

void draw(t_fractol *fractol)
{
	fractol->kernel.render(&fractol->view, &fractol->img);
	mlx_put_image_to_window(fractol->mlx, fractol->window, fractol->img.img, 0, 0);
}

t_fractol fractol_init()
{
	t_fractol	s;

	s.mlx = mlx_init();
	s.window = mlx_new_window(s.mlx, 1920, 1080, "Fractol");
	s.img.img = mlx_new_image(s.mlx, 1920, 1080);
	s.img.data = (unsigned char*)mlx_get_data_addr(s.img.img, &s.img.bpp, &s.img.len, &s.img.endian);
	printf("LEN=%d\n", s.img.bpp);
	s.needs_redraw = 0;
	s.view = viewport_create(1920, 1080);
	s.kernel = mandel_ext_de;
	//mlx_expose_hook(s.window, ctl_expose, &s);
	draw(&s);
	mlx_hook(s.window, EVENT_MOUSEDOWN, MASK_BUTTON_PRESS, ctl_mousedown, &s);
	mlx_hook(s.window, EVENT_MOUSEUP, MASK_BUTTON_RELEASE, ctl_mouseup, &s);
	mlx_hook(s.window, EVENT_MOUSEMOVE, MASK_LEAVE_WINDOW, ctl_mousemove, &s);
	mlx_hook(s.window, EVENT_KEYDOWN, MASK_KEY_PRESS, ctl_keydown, &s);
	mlx_hook(s.window, EVENT_KEYUP, MASK_KEY_RELEASE, ctl_keyup, &s);
	mlx_loop(s.mlx);
	return (s);
}

void		fractol_deinit(t_fractol *fractol)
{
	mlx_destroy_image(fractol->mlx, fractol->img.img);
	mlx_destroy_window(fractol->mlx, fractol->window);
	mlx_loop_end(fractol->mlx);
}

int main()
{
	fractol_init();

	return (0);
}

