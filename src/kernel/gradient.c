/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "gradient.h"
#include "kernel/color.h"
#include <math.h>

t_gradient
gradient_new(const struct s_gr_color *colors, size_t size)
{
	size_t	i;
	float	scale;

	i = 0;
	scale = colors[0].weight;
	while (++i < size)
		scale += colors[i].weight;
	return ((t_gradient){size, colors, scale});
}

inline t_color
gradient_get(const t_gradient *g, float f)
{
	const struct s_gr_color	*col_a;
	const struct s_gr_color	*col_b;
	float					v;

	if (f > 1.0)
		f = modff(f, &v);
	else if (f < 0.0)
		f = modff(f, &v);
	f = modff(f * g->scale, &v);
	col_a = &g->colors[(int)v];
	col_b = &g->colors[((int)v + 1) % g->size];
	v *= col_a->weight + col_b->weight;
	v = col_a->weight / v;
	return (color_lerp(col_a->color, col_b->color, v));
}
