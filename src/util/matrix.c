/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "matrix.h"
#include "vector.h"

inline void	mat_mul(t_mat2d *a, const t_mat2d *const b)
{
	*a = (t_mat2d){{
		a->data[0] * b->data[0] + a->data[1] * b->data[2],
		a->data[0] * b->data[1] + a->data[1] * b->data[3],
		a->data[2] * b->data[0] + a->data[3] * b->data[2],
		a->data[2] * b->data[1] + a->data[3] * b->data[3],
	}};
}

inline t_vec2d	mat_mul_vec(const t_mat2d *const mat, const t_vec2d *const vec)
{
	return ((t_vec2d){
		.x = mat->data[0] * vec->x + mat->data[1] * vec->y,
		.y = mat->data[2] * vec->x + mat->data[3] * vec->y,
	});
}

inline void	mat_invert(t_mat2d *mat)
{
	const double	scale = 1.0
		/ (mat->data[0] * mat->data[3] - mat->data[1] * mat->data[2]);

	*mat = (t_mat2d){{
		+ scale * mat->data[3],
		- scale * mat->data[1],
		+ scale * mat->data[2],
		- scale * mat->data[0],
	}};
}
