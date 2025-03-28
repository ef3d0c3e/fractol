/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Math helper functions
 */

#include <util/math.h>

inline float	lerpf(const float a, const float b, const float f)
{
	return ((a * (1.f - f)) + (b * f));
}

inline double	fsign(double x)
{
	if (x < 0)
		return (-1);
	return (1);
}

inline int	max(int x, int y)
{
	if (x < y)
		return (y);
	return (x);
}

inline int	min(int x, int y)
{
	if (x > y)
		return (y);
	return (x);
}
