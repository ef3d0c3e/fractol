/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"
#include "ui/event.h"

static int	clamp(int x, int min, int max)
{
	if (x < min)
		return (min);
	else if (x > max)
		return (max);
	return (x);
}

static void	selector_text(t_fractol *f, const char *text, t_pos pos, uint32_t color)
{
	drawqueue_push(&f->ui.ui_queue, (t_draw_item){
		.item = DRAW_TEXT,
		.draw.text = {
			.color = 0x0,
			.pos = {pos.x + 1, pos.y + 1},
			.str = text,
		}
	});
	drawqueue_push(&f->ui.ui_queue, (t_draw_item){
		.item = DRAW_TEXT,
		.draw.text = {
			.color = color,
			.pos = pos,
			.str = text,
		}
	});
}


void		fractol_selector(t_fractol *f)
{
	static const t_color	colors[] = {{0xFFFFFF}, {0x00FF00}, {0x0000FF}};
	const char				*name;
	int						id;

	if (ev_key_pressed(&f->ui, KEY_S))
		f->selector_shown = !f->selector_shown;
	if (!f->selector_shown)
		return ;
	f->selector_id = clamp(f->selector_id + ev_key_held(&f->ui, KEY_ARROW_DOWN)
			- ev_key_held(&f->ui, KEY_ARROW_UP), 0, f->kernel_count - 1);
	id = 0;
	while ((name = kernel_name(id)))
	{
		selector_text(f, name, (t_pos){12, 12 * (id - f->selector_id + 3)}, colors[(id == f->selector_id && id != f->kernel_id)
			+ 2 * (id == f->kernel_id)].color);
		++id;
	}
	drawqueue_push(&f->ui.ui_queue, (t_draw_item){
		.item = DRAW_TEXT,
		.draw.text = {
			.color = colors[1].color,
			.pos = {3, 12 * 3},
			.str = ">",
		}
	});
	if (ev_key_pressed(&f->ui, KEY_RETURN) && f->kernel_id != f->selector_id)
	{
		kernel_deinit(f->kernel, &f->kernel_settings);
		f->kernel_id = f->selector_id;
		free(f->view.data);
		f->kernel = kernel_init(f->selector_id, &f->view, &f->kernel_settings);
		f->last_view = f->view;
		f->needs_render = true;
	}
}
