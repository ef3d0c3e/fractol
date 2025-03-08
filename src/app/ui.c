/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"
#include "util/util.h"

/* Display iteration count */
static inline void	iter_count(t_fractol *f)
{
	const int	length = log10(f->max_iter) + (!f->max_iter);
	static char	buf[64];
	int			x;
	size_t		i;

	ft_memcpy(buf, "iter: ", 6);
	x = f->max_iter;
	i = 0;
	while (x)
	{
		buf[6 + length - i] = (x % 10) + '0';
		x /= 10;
		++i;
	}
	buf[6 + length + 1] = '\0';
	drawqueue_push(&f->ui.ui_queue, (t_draw_item){
		.item = DRAW_TEXT_SHADOW,
		.draw.text_shadow = {
		.pos = {2, f->ui.size.y - 8},
		.color = 0xFFFFFF,
		.shadow = 0x000000,
		.str = buf,
	}});
}

void	fractol_ui(t_fractol *f)
{
	if (ev_key_held(&f->ui, KEY_Q))
		f->max_iter = min(20000, f->max_iter + 3);
	else if (ev_key_held(&f->ui, KEY_A))
		f->max_iter = max(1, f->max_iter - 3);
	else if (ev_key_pressed(&f->ui, KEY_F) && f->kernel->flags & USE_GRADIENT)
		gradient_randomize(&f->kernel_settings.gradient, 8);
	if (ev_key_pressed(&f->ui, KEY_Z))
		fractol_screenshot(f);
	iter_count(f);
}
