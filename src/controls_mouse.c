#include "controls.h"
#include "fractol.h"
#include <stdio.h>

int	ctl_mousedown(enum e_mousecode code, int x, int y, t_fractol *f)
{
	//if (code != MOUSE_WHEEL_UP)
	//	return (0);
	if (code != MOUSE_LEFT_DOWN)
		return (0);
	f->ui.mouse_pos.x = x;
	f->ui.mouse_pos.y = y;
	f->ui.mouse_down = true;

	return (0);
}

int	ctl_mouseup(enum e_mousecode code, int x, int y, t_fractol *f)
{
	f->ui.mouse_down = false;
	return (0);
}

int	ctl_mousemove(int x, int y, t_fractol *f)
{
	if (!f->ui.mouse_down)
		return (0);
	f->ui.mouse_delta.x = x - f->ui.mouse_pos.x;
	f->ui.mouse_delta.y = y - f->ui.mouse_pos.y;
	f->ui.mouse_pos.x = x;
	f->ui.mouse_pos.y = y;
	f->ui.img_pos.x += f->ui.mouse_delta.x;
	f->ui.img_pos.y += f->ui.mouse_delta.y;
	ui_draw(f);
	return (0);
}
