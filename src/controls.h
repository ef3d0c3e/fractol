#ifndef	CONTROLS_H
# define CONTROLS_H

# include "fractol.h"

int	ctl_mousedown(enum e_mousecode code, int x, int y, t_fractol *f);
int	ctl_mouseup(enum e_mousecode code, int x, int y, t_fractol *f);
int	ctl_mousemove(int x, int y, t_fractol *f);

int	ctl_keyup(enum e_keycode code, t_fractol *f);
int	ctl_keydown(enum e_keycode code, t_fractol *f);

#endif //	CONTROLS_H
