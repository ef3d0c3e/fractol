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

/**
 * @file Main UI
 */

#include <app/fractol.h>
#include <ui/event.h>
#include <util/util.h>

#include <mlx.h>
#include <stddef.h>

/* Writes int to buffer */
static inline void	write_int(char **buf, int x)
{
	const int	length = log10(abs(x)) + (!x);
	size_t		i;

	if (x < 0)
		*(*buf)++ = '-';
	x *= -(x < 0) + (x >= 0);
	i = 0;
	while (x)
	{
		(*buf)[length - i - 1] = (x % 10) + '0';
		x /= 10;
		++i;
	}
	*buf += length;
}

/* Display iteration count */
static inline void	iter_count(t_fractol *f)
{
	static char	str[2550];
	char		*ptr;

	ptr = (char *)ft_memcpy_unaligned(str, "iter: ", 6) + 7;
	write_int(&ptr, f->max_iter);
	ptr = (char *)ft_memcpy_unaligned(ptr, " | downsampling: ", 17) + 18;
	write_int(&ptr, f->downsampling);
	ptr = (char *)ft_memcpy_unaligned(ptr, " | oversampling: ", 17) + 18;
	write_int(&ptr, f->oversampling);
	*ptr = '\0';
	drawqueue_push(&f->ui.ui_queue, (t_draw_item){
		.item = DRAW_TEXT_SHADOW,
		.draw.text_shadow = {
		.pos = {2, f->ui.size.y - 8},
		.color = 0xFFFFFF,
		.shadow = 0x000000,
		.str = str,
	}});
}

void	fractol_ui(t_fractol *f)
{
	if (ev_key_held(&f->ui, KEY_Q))
		f->max_iter = min(20000, f->max_iter + 3);
	else if (ev_key_held(&f->ui, KEY_A))
		f->max_iter = max(1, f->max_iter - 3);
	else if (ev_key_pressed(&f->ui, KEY_F) && f->kernel->flags & USE_GRADIENT)
		gradient_randomize(&f->kernel_settings.gradient, 4);
	if (ev_key_pressed(&f->ui, KEY_Z))
		fractol_screenshot(f);
	if (ev_key_pressed(&f->ui, KEY_ESC))
	{
		mlx_loop_end(f->mlx);
		return ;
	}
	iter_count(f);
}
