#ifndef FRACTOL_H
# define FRACTOL_H

# include "kernel.h"
# include "viewport.h"
# include "ui.h"

# include "../minilibx-linux/mlx_int.h"
# include "draw_buffer.h"
# include <stdbool.h>

typedef struct	s_fractol
{
	// Mlx data
	t_xvar			*mlx;
	t_win_list		*window;
	struct s_image	img;

	t_ui			ui;

	// Rendering data
	t_viewport		view;
	t_kernel		kernel;
}	t_fractol;

t_fractol	fractol_init();
int			fractol_deinit(t_fractol *fractol);


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
	MOUSE_LEFT = 1,
	MOUSE_MIDDLE = 2,
	MOUSE_RIGHT = 3,
	MOUSE_WHEEL_DOWN = 4,
	MOUSE_WHEEL_UP = 5,
};

enum e_eventcode {
	EVENT_KEYDOWN = 2,
	EVENT_KEYUP = 3,
	EVENT_MOUSEDOWN = 4,
	EVENT_MOUSEUP = 5,
	EVENT_MOUSEMOVE = 6,
	EVENT_EXPOSE = 12,
	EVENT_DESTROY = 17
};

enum e_evmask {
	MASK_NoEventMask              = (0L),
	MASK_KEY_PRESS                = (1L<<0),
	MASK_KEY_RELEASE              = (1L<<1),
	MASK_BUTTON_PRESS             = (1L<<2),
	MASK_BUTTON_RELEASE           = (1L<<3),
	MASK_EnterWindowMask          = (1L<<4),
	MASK_LEAVE_WINDOW             = (1L<<5),
	MASK_PointerMotionMask        = (1L<<6),
	MASK_PointerMotionHintMask    = (1L<<7),
	MASK_Button1MotionMask        = (1L<<8),
	MASK_Button2MotionMask        = (1L<<9),
	MASK_Button3MotionMask        = (1L<<10),
	MASK_Button4MotionMask        = (1L<<11),
	MASK_Button5MotionMask        = (1L<<12),
	MASK_ButtonMotionMask         = (1L<<13),
	MASK_KeymapStateMask          = (1L<<14),
	MASK_ExposureMask             = (1L<<15),
	MASK_VisibilityChangeMask     = (1L<<16),
	MASK_StructureNotifyMask      = (1L<<17),
	MASK_ResizeRedirectMask       = (1L<<18),
	MASK_SubstructureNotifyMask   = (1L<<19),
	MASK_SubstructureRedirectMask = (1L<<20),
	MASK_FocusChangeMask          = (1L<<21),
	MASK_PropertyChangeMask       = (1L<<22),
	MASK_ColormapChangeMask       = (1L<<23),
	MASK_OwnerGrabButtonMask      = (1L<<24),
};

#endif // FRACTOL_H
