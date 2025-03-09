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

/**
 * @file Color utilities
 */

#include <kernel/color.h>
#include <util/math.h>

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
	return ((t_color){.channels = {
			.b = lerpf(first.channels.b, second.channels.b, f),
			.g = lerpf(first.channels.g, second.channels.g, f),
			.r = lerpf(first.channels.r, second.channels.r, f),
			.a = 0,
		}});
}

inline t_color
	color_from_hsv(double h, double s, double v)
{
	const int		t = min(5, max(0, (6 * h)));
	double			a[6];

	a[0] = v * (1 - s);
	a[1] = v * (1 - s * (6 * h - floor(6 * h)));
	a[2] = v * (1 - s * (1 - (6 * h - floor(6 * h))));
	a[3] = v;
	a[4] = v;
	a[5] = v;
	if (s != 0.0)
	{
		a[3] = a[(const int []){3, 1, 0, 0, 2, 3}[t]];
		a[4] = a[(const int []){2, 4, 4, 1, 0, 0}[t]];
		a[5] = a[(const int []){0, 0, 2, 5, 5, 1}[t]];
	}
	return ((t_color){.channels = {
			.r = fmin(fmax(255 * a[3] + 0.5, 0), 255),
			.g = fmin(fmax(255 * a[4] + 0.5, 0), 255),
			.b = fmin(fmax(255 * a[5] + 0.5, 0), 255),
			.a = 0
		}});
}
