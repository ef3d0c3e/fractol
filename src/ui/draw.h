#ifndef DRAW_H
# define DRAW_H

# include "mlx_int.h"
# include "../ui.h"
# include <stdint.h>

/**
 * @brief Drawable primitives
 */
enum	e_draw_item
{
	DRAW_RECT,
	DRAW_LINE,
	DRAW_CIRCLE,
};

typedef union u_draw_item
{
	struct s_draw_rect
	{
		enum e_draw_item	item;
		uint32_t			color;
		t_pos				top_left;
		t_pos				bottom_right;
		bool				fill;
	} rect;

	struct s_draw_line
	{
		enum e_draw_item 	item;
		uint32_t			color;
		t_pos				start;
		t_pos				end;
	} line;

	struct s_draw_circle
	{
		enum e_draw_item	item;
		uint32_t			color;
		t_pos				center;
		double				radius;
		bool				fill;
	} circle;
}	t_draw_item;

/**
 * @brief Draw item to image
 */
void	draw(t_img *image, const t_draw_item *item);

typedef struct s_drawqueue
{
	size_t		capacity;
	size_t		size;
	t_draw_item *queue;
}	t_drawqueue;

/**
 * @brief Creates a new draw queue
 */
t_drawqueue
drawqueue_new();

void
drawqueue_free(t_drawqueue *d);

void
drawqueue_push(t_drawqueue *d, const t_draw_item item);

void
drawqueue_clear(t_drawqueue *d);

/**
 * @brief Renders to image
 */
void
drawqueue_render(const t_drawqueue *d, t_img *img);

#endif // DRAW_H
