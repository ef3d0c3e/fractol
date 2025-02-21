#include "fractol.h"



void	fractol_bar(t_fractol *f)
{
	t_pos cursor;

	cursor = (t_pos){2, f->ui.size.y - 8};

	drawqueue_push(&f->ui.ui_queue, (t_draw_item){
		.item = DRAW_TEXT,
		.draw.text = {
			.pos = cursor,
			.color = 0xFFFFFF,
			.str = "iter:",
		}
	});
}
