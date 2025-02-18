#include "../minilibx-linux/mlx.h"
#include "kernel.h"
#include "matrix.h"
#include "ui.h"
#include "viewport.h"
#include "fractol.h"
#include "controls.h"
#include "viewport_linear.h"

t_fractol fractol_init()
{
	t_fractol	s;

	s.ui = ui_init();

	/// MLX_INIT
	s.mlx = mlx_init();
	s.window = mlx_new_window(s.mlx, 1920, 1080, "Fractol");
	s.img.img = mlx_new_image(s.mlx, 1920, 1080);
	s.img.data = (unsigned char*)mlx_get_data_addr(s.img.img, &s.img.bpp, &s.img.len, &s.img.endian);

	mlx_loop_hook(s.mlx, ui_draw, &s);
	mlx_hook(s.window, EVENT_MOUSEDOWN, MASK_BUTTON_PRESS, ctl_mousedown, &s);
	mlx_hook(s.window, EVENT_MOUSEUP, MASK_BUTTON_RELEASE, ctl_mouseup, &s);
	mlx_hook(s.window, EVENT_MOUSEMOVE, MASK_PointerMotionMask, ctl_mousemove, &s);
	mlx_hook(s.window, EVENT_KEYDOWN, MASK_KEY_PRESS, ctl_keydown, &s);
	mlx_hook(s.window, EVENT_KEYUP, MASK_KEY_RELEASE, ctl_keyup, &s);
	mlx_hook(s.window, EVENT_DESTROY, 0, fractol_deinit, &s);
	
	// Viewport
	struct s_viewport_linear_data view_data = view_linear_data(
			(t_mat2d){{ 1.0, 0.0, 0.0, 1.0 }});
	s.view = viewport_create(
			pos_new(1920, 1080),
			view_linear_screen_to_space,
			view_linear_space_to_screen,
			&view_data);
	s.kernel = mandel_ext_de;

	mlx_loop(s.mlx);
	return (s);
}

int		fractol_deinit(t_fractol *fractol)
{
	mlx_destroy_image(fractol->mlx, fractol->img.img);
	mlx_destroy_window(fractol->mlx, fractol->window);
	mlx_loop_end(fractol->mlx);
	return (0);
}

int main()
{
	fractol_init();

	return (0);
}

