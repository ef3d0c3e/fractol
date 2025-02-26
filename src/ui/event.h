/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef EVENT_H
# define EVENT_H

/**
 * @file Event handlers
 */

# include <util/pos.h>
# include <stdbool.h>

typedef struct s_fractol	t_fractol;
typedef struct s_ui			t_ui;

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
	KEY_RETURN = 0xff0d,
	// Arrow
	KEY_ARROW_LEFT = 65361,
	KEY_ARROW_UP,
	KEY_ARROW_RIGHT,
	KEY_ARROW_DOWN,
};

enum e_mousecode
{
	MOUSE_NONE,
	MOUSE_LEFT = 1,
	MOUSE_MIDDLE = 2,
	MOUSE_RIGHT = 3,
	MOUSE_WHEEL_DOWN = 4,
	MOUSE_WHEEL_UP = 5,
};

enum e_eventcode
{
	EVENT_KEYDOWN = 2,
	EVENT_KEYUP = 3,
	EVENT_MOUSEDOWN = 4,
	EVENT_MOUSEUP = 5,
	EVENT_MOUSEMOVE = 6,
	EVENT_EXPOSE = 12,
	EVENT_DESTROY = 17
};

enum e_evmask
{
	MASK_NONE = (0L),
	MASK_KEY_PRESS = (1L<<0),
	MASK_KEY_RELEASE = (1L<<1),
	MASK_BUTTON_PRESS = (1L<<2),
	MASK_BUTTON_RELEASE = (1L<<3),
	MASK_EnterWindowMask = (1L<<4),
	MASK_LEAVE_WINDOW = (1L<<5),
	MASK_POINTER_MOTION = (1L<<6),
	MASK_PointerMotionHintMask = (1L<<7),
	MASK_Button1MotionMask = (1L<<8),
	MASK_Button2MotionMask = (1L<<9),
	MASK_Button3MotionMask = (1L<<10),
	MASK_Button4MotionMask = (1L<<11),
	MASK_Button5MotionMask = (1L<<12),
	MASK_ButtonMotionMask = (1L<<13),
	MASK_KeymapStateMask = (1L<<14),
	MASK_ExposureMask = (1L<<15),
	MASK_VisibilityChangeMask = (1L<<16),
	MASK_StructureNotifyMask = (1L<<17),
	MASK_ResizeRedirectMask = (1L<<18),
	MASK_SubstructureNotifyMask = (1L<<19),
	MASK_SubstructureRedirectMask = (1L<<20),
	MASK_FocusChangeMask = (1L<<21),
	MASK_PropertyChangeMask = (1L<<22),
	MASK_ColormapChangeMask = (1L<<23),
	MASK_OwnerGrabButtonMask = (1L<<24),
};

/**
 * @brief Sets up the events
 *
 * Registers handlers to mlx
 *
 * @param fractol Program
 */
void	event_setup(t_fractol *fractol);

/**
 * @brief Types of event
 */
enum e_ev_type
{
	UI_NONE,
	UI_KEY_PRESS,
	UI_KEY_RELEASE,
	UI_MOUSE_PRESS,
	UI_MOUSE_RELEASE,
	UI_MOUSE_MOVE,
	UI_WNIDOW_RESIZE,
};

/**
 * @brief Event data
 */
typedef struct s_event
{
	enum e_ev_type	type;

	union u_event
	{
		/**
		 * @brief Keyboard press/release event
		 */
		struct s_ev_keyboard
		{
			enum e_keycode		code;
		}	keyboard;
		/**
		 * @brief Mouse button event
		 */
		struct s_ev_mouse
		{
			t_pos				from;
			t_pos				to;
			enum e_mousecode	code;
		}	mouse;
		/**
		 * @brief Mouse move event
		 */
		struct s_ev_mouse_move
		{
			t_pos				from;
			t_pos				to;
		}	mouse_move;
	}	event;
}	t_event;

/**
 * @brief Returns true if key `code` has been pressed (e.g released)
 *
 * @param ui The ui
 * @param code The keycode
 *
 * @returns true if key `code` is released
 */
bool	ev_key_pressed(t_ui *ui, enum e_keycode code);
/**
 * @brief Returns true if key `code` is held
 *
 * @param ui The ui
 * @param code The keycode
 *
 * @returns true if key `code` is held
 */
bool	ev_key_held(t_ui *ui, enum e_keycode code);
/**
 * @brief Returns true if button `code` has been pressed (e.g released)
 *
 * @param ui The ui
 * @param code The button code
 *
 * @returns true if key `code` is released
 */
bool	ev_mouse_pressed(t_ui *ui, enum e_mousecode code);
/**
 * @brief Returns true if button `code` is held
 *
 * @param ui The ui
 * @param code The button code
 *
 * @returns true if key `code` is held
 */
bool	ev_mouse_held(t_ui *ui, enum e_mousecode code);
/**
 * @brief Gets the mouse wheel delta
 *
 * @param ui The ui
 *
 * @returns +1 for scroll up, -1 for down
 */
int		ev_wheel_delta(t_ui *ui);

#endif // EVENT_H
