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
#include "vector.h"

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

inline void
	vec_apply(t_vec2d *a, double (*fn)(const double x))
{
	a->x = fn(a->x);
	a->y = fn(a->y);
}
