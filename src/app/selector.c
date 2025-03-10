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

/**
 * @file Selector UI
 */

#include <app/fractol.h>

static bool	draw_item(t_fractol *f, t_pos id, const char *name)
{
	t_color	color;

	color.color = 0xFFFFFF;
	if (id.x == f->selector_pos.x && id.y == f->selector_pos.y)
		color.color = 0x00FF00;
	if (id.x == 0 && id.y == f->kernel_id)
		color.color = 0xFF0000;
	drawqueue_push(&f->ui.ui_queue, (t_draw_item){
		.item = DRAW_TEXT_SHADOW,
		.draw.text_shadow = {
		.color = color_lerp(color, (t_color){0},
			0.33 * (id.x != f->selector_pos.x)).color,
		.shadow = 0,
		.pos = {12 + 256 * (id.x - f->selector_pos.x * (f->ui.size.x < 512)),
		12 * (id.y - f->selector_pos.y + 3)},
		.str = name}});
	return (ev_key_pressed(&f->ui, KEY_RETURN) && f->selector_pos.x == id.x
		&& f->selector_pos.y == id.y);
}

static void	selector_kernel(t_fractol *f)
{
	const char	*name;
	int			id;

	if (f->selector_pos.x == 0)
		f->selector_pos.y = min(max(f->selector_pos.y, 0), f->kernel_count - 1);
	id = 0;
	name = kernel_name(id);
	while (name)
	{
		if (draw_item(f, (t_pos){0, id}, name)
			&& f->kernel_id != f->selector_pos.y)
		{
			kernel_deinit(f->kernel, &f->kernel_settings);
			f->kernel_id = f->selector_pos.y;
			if (f->has_next_view)
				f->view = f->next_view;
			f->kernel = kernel_init(f->kernel_id, &f->view,
					&f->kernel_settings);
			f->next_view = f->view;
			f->needs_render = true;
		}
		name = kernel_name(++id);
	}
}

static void	selector_options_1(t_fractol *f)
{
	const bool	has_gradient = (f->kernel->flags & USE_GRADIENT) != 0;

	if (f->selector_pos.x == 1)
		f->selector_pos.y = min(max(f->selector_pos.y, 0), 14);
	if (draw_item(f, (t_pos){1, 0}, "Render"))
		f->needs_render = true;
	if (draw_item(f, (t_pos){1, 1}, "Upsample"))
		f->needs_resample = true;
	if (draw_item(f, (t_pos){1, 2}, "Randomize Gradient (3)") && has_gradient)
		gradient_randomize(&f->kernel_settings.gradient, 3);
	if (draw_item(f, (t_pos){1, 3}, "Randomize Gradient (6)") && has_gradient)
		gradient_randomize(&f->kernel_settings.gradient, 6);
	if (draw_item(f, (t_pos){1, 4}, "Randomize Gradient (16)") && has_gradient)
		gradient_randomize(&f->kernel_settings.gradient, 16);
	if (draw_item(f, (t_pos){1, 5}, "Reset viewport"))
	{
		f->view.view = (t_mat2d){{-f->ui.size.x / (double)f->ui.size.y,
			f->ui.size.x / (double)f->ui.size.y, f->kernel->default_viewport
			.data[2], f->kernel->default_viewport.data[3]}};
		f->next_view = f->view;
		f->has_next_view = false;
		f->needs_render = true;
	}
	if (draw_item(f, (t_pos){1, 6}, "Sceenshot to 'screenshot.ppm'"))
		fractol_screenshot(f);
}

static void	selector_options_2(t_fractol *f)
{
	if (draw_item(f, (t_pos){1, 7}, "Iter +100"))
		f->max_iter = min(f->max_iter + 100, 50000);
	if (draw_item(f, (t_pos){1, 8}, "Iter -100"))
		f->max_iter = max(f->max_iter - 100, 1);
	if (draw_item(f, (t_pos){1, 9}, "Downsample +1"))
		f->downsampling = min(f->downsampling + 1, 16);
	if (draw_item(f, (t_pos){1, 10}, "Downsample -1"))
		f->downsampling = max(f->downsampling - 1, 1);
	if (draw_item(f, (t_pos){1, 11}, "Oversample +1"))
		f->oversampling = min(f->oversampling + 1, 8);
	if (draw_item(f, (t_pos){1, 12}, "Oversample -1"))
		f->oversampling = max(f->oversampling - 1, 1);
	if (draw_item(f, (t_pos){1, 13}, "Oversampling Debug"))
		f->needs_resample_debug = true;
	if (draw_item(f, (t_pos){1, 14}, "Gradient Debug")
			&& f->kernel->flags & USE_GRADIENT)
		f->needs_gradient_debug = true;
}

void	fractol_selector(t_fractol *f)
{
	static const t_color	colors[] = {{0xFFFFFF}, {0x00FF00}, {0x0000FF}};

	if (ev_key_pressed(&f->ui, KEY_S))
		f->selector_shown = !f->selector_shown;
	if (!f->selector_shown)
		return ;
	f->selector_pos.y += ev_key_held(&f->ui, KEY_ARROW_DOWN)
		- ev_key_held(&f->ui, KEY_ARROW_UP);
	f->selector_pos.x += ev_key_held(&f->ui, KEY_ARROW_RIGHT)
		- ev_key_held(&f->ui, KEY_ARROW_LEFT);
	f->selector_pos.x = min(max(f->selector_pos.x, 0), 1);
	selector_kernel(f);
	selector_options_1(f);
	selector_options_2(f);
	drawqueue_push(&f->ui.ui_queue, (t_draw_item){
		.item = DRAW_TEXT_SHADOW,
		.draw.text_shadow = {
		.color = colors[1].color,
		.shadow = 0,
		.pos = {256 * (f->selector_pos.x * (f->ui.size.x >= 512)), 12 * 3},
		.str = "->"}});
}
