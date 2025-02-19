#include "controls.h"
#include "fractol.h"
#include "viewport/viewport.h"
#include <stdio.h>

int	ctl_mousedown(enum e_mousecode code, int x, int y, t_fractol *f)
{
	printf("down=%d\n", code);
	if (code == MOUSE_WHEEL_UP)
		return (view_move(&f->view, (t_pos){0, 0}, (t_pos){0, 0}, -3), 0);
	else if (code == MOUSE_WHEEL_DOWN)
		return (view_move(&f->view, (t_pos){0, 0}, (t_pos){0, 0}, 3), 0);
	else if (code != MOUSE_LEFT)
		return (0);
	f->ui.mouse_pos.x = x;
	f->ui.mouse_pos.y = y;
	f->ui.mouse_down = true;

	return (0);
}

int	ctl_mouseup(enum e_mousecode code, int x, int y, t_fractol *f)
{
	printf("up=%d\n", code);
	f->ui.mouse_down = false;
	return (0);
}

int	ctl_mousemove(int x, int y, t_fractol *f)
{
	const t_pos	pos = {x, y};

	if (!f->ui.mouse_down)
		return (0);

	view_move(&f->view, f->ui.mouse_pos, pos, 0);
	f->ui.mouse_delta.x = x - f->ui.mouse_pos.x;
	f->ui.mouse_delta.y = y - f->ui.mouse_pos.y;
	f->ui.mouse_pos = pos;
	f->ui.img_pos.x += f->ui.mouse_delta.x;
	f->ui.img_pos.y += f->ui.mouse_delta.y;
	ui_draw(f);
	return (0);
}
