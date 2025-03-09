/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "color.h"

inline t_colvec
	colvec_new(float r, float g, float b, float a)
{
	return ((t_colvec){
		.channels.b = b,
		.channels.g = g,
		.channels.r = r,
		.channels.a = a,
	});
}

inline void
	colvec_sample(t_colvec *col, t_color sample, float factor)
{
	const float	f = factor / 255.f;

	col->v[0] += sample.channels.b * f;
	col->v[1] += sample.channels.g * f;
	col->v[2] += sample.channels.r * f;
	col->v[3] += sample.channels.a * f;
}

inline t_color
	colvec_to_color(const t_colvec *col, float stretch)
{
	const float	f = 255.f / stretch;

	return ((t_color){
		.channels.b = col->v[0] * f,
		.channels.g = col->v[1] * f,
		.channels.r = col->v[2] * f,
		.channels.a = 0,
	});
}
