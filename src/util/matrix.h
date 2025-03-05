/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"

typedef union u_mat2d
{
	struct s_mat2d_values
	{
		double	a;
		double	b;
		double	c;
		double	d;
	}			v;
	double		data[4];
}	t_mat2d;

/**
 * @brief Multiplies two matrices, stores the result in the first parameter
 *
 * @param a (out) The first matrix
 * @param b The second matrix
 */
void
mat_mul(t_mat2d *a, const t_mat2d *const b);
/**
 * @brief Multiplies a matrix with a vector (i.e applies linear transform)
 *
 * @param mat The transformation matrix
 * @param vec Vector to transform
 *
 * @returns mat times vec
 */
t_vec2d
mat_mul_vec(const t_mat2d *const mat, const t_vec2d *const vec);
/**
 * @brief Multiplies a matrix with a vector (i.e applies linear transform)
 *
 * @param vec Vector to transform
 * @param mat The transformation matrix
 *
 * @returns vec times mat
 */
t_vec2d
vec_mul_mat(const t_vec2d *const vec, const t_mat2d *const mat);
/**
 * @brief Inverts a matrix
 *
 * @param mat (out) Matrix to invert
 */
void
mat_invert(t_mat2d *mat);

#endif // MATRIX_H
