#include "draw.h"

static inline void	draw_rect(t_img *img, const struct s_draw_rect *rect)
{
	t_pos	pos;

	pos.y = rect->top_left.y;
	while (pos.y < rect->bottom_right.y)
	{
		pos.x = rect->top_left.x;
		while (pos.x < rect->bottom_right.x)
		{
			
			++pos.x;
		}
		++pos.y;
	}
}

static inline void	draw_line(t_img *img, const struct s_draw_line *line)
{

}

static inline void	draw_circle(t_img *img, const struct s_draw_circle *circle)
{

}

inline void	draw(t_img *img, const t_draw_item *item)
{
	static void(*const drawer_table[])(t_img *img, const t_draw_item *item) = {
		[DRAW_RECT] = (void*)draw_rect,
		[DRAW_LINE] = (void*)draw_line,
		[DRAW_CIRCLE] = (void*)draw_circle,
	};
}
