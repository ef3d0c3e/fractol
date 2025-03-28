/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file double floating point vector implementation
 */

#include <util/vector.h>
#include <math.h>

inline void
	vec_add(t_vec2d *a, const t_vec2d *const b)
{
	a->x += b->x;
	a->y += b->y;
}

inline void
	vec_mul(t_vec2d *a, const double f)
{
	a->x *= f;
	a->y *= f;
}

inline double	vec_norm(const t_vec2d *a)
{
	return (sqrt(a->x * a->x + a->y * a->y));
}

inline double	vec_norm_sqr(const t_vec2d *a)
{
	return (a->x * a->x + a->y * a->y);
}
