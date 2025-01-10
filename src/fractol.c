#include "../minilibx-linux/mlx.h"
#include "fractol.h"

struct s_fractol fractol_init()
{
	struct s_fractol	s;

	s.mlx = mlx_init();
	s.window = mlx_new_window(s.mlx, 1920, 1080, "Fractol");
	s.img.img = *(t_img*)mlx_new_image(s.mlx, 1920, 1080);
	s.img.data = (unsigned char*)mlx_get_data_addr(&s.img.img, &s.img.bpp, &s.img.len, &s.img.endian);
	mlx_key_hook(s.window, ctl_keyboard, &s);
	//mlx_expose_hook(s.window, ctl_expose, &s);
	mlx_hook(s.window, 4, 0x4, ctl_mousekey, &s);
	mlx_hook(s.window, 5, 0x8, ctl_mousekey, &s);
	mlx_hook(s.window, 6, 0x20, ctl_mousemove, &s);
	mlx_loop(s.mlx);
	s.needs_redraw = 1;
	return (s);
}

void draw(struct s_fractol *s)
{
	mlx_put_image_to_window(s->mlx, s->window, &s->img, 0, 0);
}

void		fractol_deinit(struct s_fractol *s)
{
	mlx_destroy_window(s->mlx, s->window);
	//FIXME: mlx_destroy_image(s->mlx, &s->img.img);
}

int main()
{
	fractol_init();

	return (0);
}

