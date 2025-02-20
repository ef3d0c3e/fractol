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
#include <stdio.h>

t_gradient
gradient_new(const struct s_gr_color *colors, size_t size)
{
	size_t	i;
	float	scale;

	i = 0;
	scale = colors[0].weight / 2;
	while (++i < size - 1)
		scale += colors[i].weight;
	scale += colors[size - 1].weight / 2;
	return ((t_gradient){size, colors, scale});
}

inline t_color
gradient_get(const t_gradient *g, float f)
{
	const struct s_gr_color	*col_a;
	const struct s_gr_color	*col_b;
	float					v;


	if (g->size == 1)
		return (g->colors[0].color);
	else if (f > 1.0)
		f = modff(f, &v);
	else if (f < 0.0)
		f = modff(-f, &v);
	if (f == 0 || g->size == 1)
		return (g->colors[0].color);
	else if (f == 1)
		return (g->colors[g->size - 1].color);

	int index = 0;
	float next = (g->colors[0].weight + g->colors[1].weight) / 2;
	float start = 0;
	f *= g->scale;
	while (next < f && index < g->size - 2)
	{
		++index;
		start = next;
		next += (g->colors[index].weight + g->colors[index + 1].weight) / 2;
	}

	float	range = (g->colors[index + 1].weight + g->colors[index].weight) / 2;
	float	center = start + g->colors[index].weight / 2;
	if (f <= center)
	{
		f = (f - start)
			/ (g->colors[index].weight / 2)
			/ 2;
	}
	else
	{
		f = 0.5 + (f - center)
			/ (g->colors[index + 1].weight / 2)
			/ 2;
	}
	
	return color_lerp(g->colors[index].color, g->colors[index + 1].color, f);

	/*
	f = modff(f * g->scale / 2, &v);
	col_a = &g->colors[(int)v % g->size];
	col_b = &g->colors[((int)v + 1) % g->size];
	v = col_a->weight + col_b->weight;
	v = ((f * v - col_a->weight)
		+ (f * v - col_b->weight))
		/ v;
	return (color_lerp(col_a->color, col_b->color, v));
	*/
}
