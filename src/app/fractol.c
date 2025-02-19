#include "../minilibx-linux/mlx.h"
#include <kernels/kernel.h>
#include <util/math.h>
#include <ui/ui.h>
#include "ui/draw.h"
#include "viewport/viewport.h"
#include "viewport/viewport_linear.h"
#include "fractol.h"
#include "controls.h"

t_fractol fractol_init()
{
	t_fractol	s;

	/// MLX_INIT
	s.mlx = mlx_init();
	s.window = mlx_new_window(s.mlx, 1920, 1080, "Fractol");

	s.ui = ui_init(s.mlx, (t_pos){1920, 1080});

	mlx_loop_hook(s.mlx, ui_draw, &s);
	mlx_hook(s.window, EVENT_MOUSEDOWN, MASK_BUTTON_PRESS, ctl_mousedown, &s);
	mlx_hook(s.window, EVENT_MOUSEUP, MASK_BUTTON_RELEASE, ctl_mouseup, &s);
	mlx_hook(s.window, EVENT_MOUSEMOVE, MASK_PointerMotionMask, ctl_mousemove, &s);
	mlx_hook(s.window, EVENT_KEYDOWN, MASK_KEY_PRESS, ctl_keydown, &s);
	mlx_hook(s.window, EVENT_KEYUP, MASK_KEY_RELEASE, ctl_keyup, &s);
	mlx_hook(s.window, EVENT_DESTROY, 0, mlx_loop_end, s.mlx);
	
	// Viewport
	struct s_viewport_linear_data view_data = view_linear_data(
			(t_mat2d){{ 1.0, 0.0, 0.0, 1.0 }});
	s.view = viewport_create(
			pos_new(1920, 1080),
			view_linear_screen_to_space,
			view_linear_space_to_screen,
			&view_data);
	s.last_view = s.view;
	s.kernel = mandel_ext_de;

	mlx_loop(s.mlx);

	ui_deinit(s.mlx, &s.ui);
	mlx_destroy_window(s.mlx, s.window);
	free(s.mlx);

	return (s);
}
