/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

/**
 * @brief Color definition
 */
typedef union u_color
{
	uint32_t	color;
	struct s_color_channels
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

/**
 * @brief Creates a color from HSV values
 *
 * @param h [0,1] Hue
 * @param s [0,1] Saturation
 * @param v [0,1] Value
 *
 * @returns A color constructed from HSV
 */
t_color
color_from_hsv(double h, double s, double v);

/**
 * @brief Floating point color type, used for image manipulations
 */
typedef union u_colvec
{
	float		v[4];
	struct s_colvec_channels
	{
		float	b;
		float	g;
		float	r;
		float	a;
	}			channels;
}	t_colvec;

/**
 * @brief Creates a new colvec from given vales
 *
 * @param r Red value [0, 1]
 * @param g Green value [0, 1]
 * @param b Blue value [0, 1]
 * @param a Alpha value [0, 1]
 *
 * @returns Created colvec from color values
 */
t_colvec
colvec_new(float r, float g, float b, float a);

/**
 * @brief Adds weighted sample to `t_colvec`
 *
 * @param col Colvec to add sample to
 * @param sampl Sample color
 * @param factor Sample weight
 */
void
colvec_sample(t_colvec *col, t_color sample, float factor);

/**
 * @brief Create `t_color` from `t_colvec`
 *
 * @param col Colvec to get `t_color` from
 * @param stretch Stretch factor, `1.f` for none
 */
t_color
colvec_to_color(const t_colvec *col, float stretch);

#endif // COLOR_H
