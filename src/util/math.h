/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MATH_H
# define MATH_H

/**
 * @file Math helpers
 */

# ifndef M_2_PI
#  define M_2_PI 6.2831853071795864769253
# endif // M_2_PI

# include "vector.h"
# include "matrix.h"
# include "pos.h"
# include <math.h>

/**
 * @brief Performs linear interpolation on floats
 *
 * @param a First value
 * @param b Second value
 * @param f Interpolation factor [0, 1]
 * 
 * @returns `(a + (b - a) * f)`
 */
float	lerpf(const float a, const float b, const float f);
/**
 * @brief Returns the sign of a value
 *
 * @param x Value to get the sign of
 *
 * @returns The sign of x, or 1 if `x == 0`
 */
double	fsign(double x);
/**
 * @brief Maximum of two values
 *
 * @param x First value
 * @param x Second value
 *
 * @return x if x >= y else y
 */
int		max(int x, int y);
/**
 * @brief Minimum of two values
 *
 * @param x First value
 * @param x Second value
 *
 * @return x if x <= y else y
 */
int		min(int x, int y);

#endif // MATH_H
