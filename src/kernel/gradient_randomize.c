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
#include "kernel/color.h"
#include "kernel/gradient.h"
#include <stdint.h>

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
	size_t				i;
	struct s_gr_color	*colors;

	colors = malloc(sizeof(struct s_gr_color) * (num + 1));
	i = 0;
	gradient_free(g);
	while (i < num)
	{
		colors[i].color.color = xorshift() % 0xFFFFFF;
		colors[i].weight = 1.f;
		++i;
	}
	colors[num] = colors[0];
	*g = gradient_new(colors, num + 1);
	free(colors);
}
