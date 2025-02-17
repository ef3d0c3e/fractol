#include "../minilibx-linux/mlx.h"
#include "kernel.h"
#include "viewport.h"
#include "fractol.h"

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
	mlx_key_hook(s.window, ctl_keyboard, &s);
	//mlx_expose_hook(s.window, ctl_expose, &s);
	draw(&s);
	mlx_hook(s.window, 4, 0x4, ctl_mousekey, &s);
	mlx_hook(s.window, 5, 0x8, ctl_mousekey, &s);
	mlx_hook(s.window, 6, 0x20, ctl_mousemove, &s);
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

