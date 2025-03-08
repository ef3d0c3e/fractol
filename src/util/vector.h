/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef VECTOR_H
# define VECTOR_H

/**
 * @brief Vector struct
 */
typedef struct s_vec2d
{
	double	x;
	double	y;
}	t_vec2d;

/**
 * @brief Single Vector struct
 */
typedef struct s_vec2f
{
	float	x;
	float	y;
}	t_vec2f;

/**
 * @brief Sums two vectors
 *
 * @param a Vector to add into
 * @param b Vector to add to `a`
 */
void
vec_add(t_vec2d *a, const t_vec2d *const b);
/**
 * @brief Multiplies a vector with a scalar
 *
 * @param a Vector to multiply
 * @param f Scalar factor
 */
void
vec_mul(t_vec2d *a, const double f);
/**
 * @brief Computes the euclidian norm of a vector
 *
 * @param a Vector to comnpute the norm of
 */
double
vec_norm(const t_vec2d *a);
/**
 * @brief Computes the squared euclidian norm of a vector
 *
 * @param a Vector to comnpute the squared norm of
 */
double
vec_norm_sqr(const t_vec2d *a);

#endif // VECTOR_H
