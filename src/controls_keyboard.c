#include "controls.h"
#include "fractol.h"
#include "ui.h"
#include <stdio.h>


int	ctl_keyup(enum e_keycode code, t_fractol *f)
{
	double	delta_x;
	double	delta_y;


	if (code == KEY_R)
	{
		f->ui.needs_render = true;
		f->ui.img_pos = pos_new(0, 0);
		ui_draw(f);
	}
	return (0);
}

int	ctl_keydown(enum e_keycode code, t_fractol *f)
{
	return (0);
}
