#ifndef UI_H
# define UI_H

#include <stdbool.h>

typedef struct s_fractol	t_fractol;

typedef struct s_pos
{
	int	x;
	int y;
}	t_pos;

t_pos	pos_new(int x, int y);

typedef struct s_ui
{
	/**
	 * @brief Set to true when in need fo re-rendering next frame
	 */
	bool	needs_render;

	bool	mouse_down;

	t_pos	img_pos;
	t_pos	mouse_pos;
	t_pos	mouse_delta;

}	t_ui;

t_ui	ui_init();
void	ui_draw(t_fractol *f);

#endif // UI_H
