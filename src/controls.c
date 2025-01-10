#include "fractol.h"
#include <stdio.h>

int	ctl_keyboard(enum e_keycode keycode, struct s_fractol *s)
{
	if (keycode == KEY_Q)
		fractol_deinit(s);
	return 0;
}

int ctl_mousekey(enum e_mousecode code, int x, int y, struct s_fractol *s) {

	printf("keycode=%d\n", code);
	return 0;
}

int ctl_mousmove(int x, int y, struct s_fractol *s) {

	printf("keycode=%d\n", code);
	return 0;
}
