/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "color.h"
#include <math.h>

inline t_color
	color_lerp(
		const t_color first,
		const t_color second,
		const double f)
{
	double	out;

	if (f > 1.0)
		return (color_lerp(first, second, modf(f, &out)));
	else if (f < 0.0)
		return (color_lerp(first, second, 1.0 - modf(f, &out)));
	return (t_color) {.channels = {
		.a = 0,
		.r = first.channels.r * f + second.channels.r * (1.0 - f),
		.g = first.channels.g * f + second.channels.g * (1.0 - f),
		.b = first.channels.b * f + second.channels.b * (1.0 - f),
	}};
}
