/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef COLOR_H
# define COLOR_H

#include <stdint.h>

/**
 * @brief Color definition
 */
typedef union u_color
{
	uint32_t	color;
	struct s_color_field
	{
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
		uint8_t	a;
	}			channels;
}	t_color;

/**
 * @brief Performs linear interpolation between two color values
 *
 * @param first First color to interpolate
 * @param second Second color to interpolate
 * @param f Lerp amount
 *
 * @returns The color `first * f + second * (1 - f)`.
 */
t_color
color_lerp(
		const t_color first,
		const t_color second,
		const double f);

#endif // COLOR_H
