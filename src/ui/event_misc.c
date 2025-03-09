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
#include <ui/event.h>
#include <ui/ui.h>
#include <app/fractol.h>

int	ev_resize(int width, int height, t_fractol *f)
{
	printf("RESIZE: %d %d\n", width, height);
	(void)f;
	return (0);
}
