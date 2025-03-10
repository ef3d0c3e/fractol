/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_misc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Misc event handlers
 */

#include <app/fractol.h>

/*
// TODO: MLX seems to be forcing a constant size
int	ev_configure(int width, int height, t_fractol *f)
{
	printf("RESIZE: %d %d\n", width, height);
	(void)f;
	return (0);
}
*/

int	ev_expose(t_fractol *f)
{
	f->ui.force_redraw = true;
	return (ui_update(f), 0);
}
