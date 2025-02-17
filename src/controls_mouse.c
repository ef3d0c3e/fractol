#include "controls.h"

int	ctl_mousedown(enum e_mousecode code, int x, int y, t_fractol *f)
{
	return (0);
}

int	ctl_mouseup(enum e_mousecode code, int x, int y, t_fractol *f)
{
	return (0);
}

int	ctl_mousemove(int x, int y, t_fractol *f)
{
	f->mouse_x = x;
	f->mouse_y = y;
	return (0);
}
