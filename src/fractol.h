#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-linux/mlx_int.h"
# include "draw_buffer.h"
# include "kernel.h"
#include "viewport.h"
# include <stdbool.h>

typedef struct	s_fractol
{
	t_xvar			*mlx;
	t_win_list		*window;
	struct s_image	img;

	bool			needs_redraw;
	t_viewport		view;
	t_kernel		kernel;
}	t_fractol;

t_fractol	fractol_init();
void		fractol_deinit(t_fractol *fractol);


/**
 * Enum for keycodes
 */
enum	e_keycode
{
	KEY_A = 'a',
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,

	// Arrows
	KEY_ARROW_LEFT = 65361,
	KEY_ARROW_UP,
	KEY_ARROW_RIGHT,
	KEY_ARROW_DOWN,
};

enum e_mousecode
{
	MOUSE_LEFT_DOWN,
	MOUSE_LEFT_UP,
	MOUSE_RIGHT_DOWN,
	MOUSE_RIGHT_UP,
	MOUSE_WHEEL_DOWN,
	MOUSE_WHEEL_UP,
};

/**
 * @brief Hook on keyboard key press
 *
 * @param code The pressed key
 * @param s Closure
 */
int					ctl_keyboard(enum e_keycode code, struct s_fractol *s);
/**
 * @brief Hook on mouse key press
 *
 * @param code The pressed key
 * @param x The mouse's x position
 * @param y The mouse's y position
 * @param s Closure
 */
int					ctl_mousekey(enum e_mousecode code, int x, int y, struct s_fractol *s);
/**
 * @brief Hook on mouse move
 *
 * @param x The mouse's x position
 * @param y The mouse's y position
 * @param s Closure
 */
int					ctl_mousemove(int x, int y, struct s_fractol *s);

#endif // FRACTOL_H
