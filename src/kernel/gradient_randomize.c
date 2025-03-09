/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_randomize.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Gradient randomizer
 */

#include <kernel/color.h>
#include <kernel/gradient.h>

#include <math.h>

/* Implementation of xorshift, for random colors */
static inline uint32_t	xorshift(void)
{
	static uint32_t	state = 1;
	uint32_t		v;

	v = state;
	state ^= state << 13;
	state ^= state >> 17;
	state ^= state << 5;
	return (v);
}

void	gradient_randomize(t_gradient *g, size_t num)
{
	static const uint32_t	max = ~(uint32_t)0;
	struct s_gr_color		*colors;
	size_t					i;
	float					h;

	gradient_free(g);
	colors = malloc(sizeof(struct s_gr_color) * (num + 1));
	i = 0;
	while (i < num)
	{
		h = fmod(xorshift() / (float)max, 1.0);
		if (h > 100 / 360.f && h < 160 / 360.f)
			h += 10 / 360.f;
		colors[i].color = color_from_hsv(h,
				0.6 + (xorshift() / (float)max) * 0.4,
				0.5 + (xorshift() / (float)max) * 0.5);
		colors[i].weight = 1.f;
		++i;
	}
	colors[num] = colors[0];
	*g = gradient_new(colors, num + 1);
	free(colors);
}
