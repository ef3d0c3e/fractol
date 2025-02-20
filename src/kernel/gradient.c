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

static t_color	get_color(const struct s_gr_color *colors, size_t size, const float total_weight, float f)
{
	int		index;
	float	next;
	float	start;

	if (size == 1)
		return (colors[0].color);
	else if (f > 1.0)
		f = modff(f, &next);
	else if (f < 0.0)
		f = modff(-f, &next);
	if (f == 0 || size == 1)
		return (colors[0].color);
	else if (f == 1)
		return (colors[size - 1].color);

	index = 0;
	next = (colors[0].weight + colors[1].weight) / 2;
	start = 0;
	f *= total_weight;
	while (next < f && index < (int)size - 2)
	{
		++index;
		start = next;
		next += (colors[index].weight + colors[index + 1].weight) / 2;
	}

	float	range = (colors[index + 1].weight + colors[index].weight) / 2;
	float	center = start + colors[index].weight / 2;
	if (f <= center)
		f = (f - start) / (colors[index].weight / 2) / 2;
	else
		f = 0.5 + (f - center) / (colors[index + 1].weight / 2) / 2;
	return color_lerp(colors[index].color, colors[index + 1].color, f);
}

t_gradient
gradient_new(const struct s_gr_color *colors, size_t size)
{
	size_t	i;
	float	scale;
	t_color	*gradient;

	i = 0;
	scale = colors[0].weight / 2;
	while (++i < size - 1)
		scale += colors[i].weight;
	scale += colors[size - 1].weight / 2;
	i = 0;
	gradient = malloc(sizeof(t_color) * 4096);
	while (i < 4096)
	{
		gradient[i] = get_color(colors, size, scale, i / 4096.f);
		++i;
	}
	return ((t_gradient){4096, gradient});
}

void
gradient_free(t_gradient *g)
{
	free(g->colors);
}

inline t_color
gradient_get(const t_gradient *g, float f)
{
	int		index;
	float	next;
	float	start;

	if (f > 1.0)
		f = modff(f, &next);
	else if (f < 0.0)
		f = modff(-f, &next);
	if (f == 0)
		return (g->colors[0]);
	else if (f == 1)
		return (g->colors[g->size - 1]);

	return (g->colors[(int)(4096 * f)]);

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
