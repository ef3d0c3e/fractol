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

void
vec_add(t_vec2d *a, const t_vec2d *const b);
void
vec_mul(t_vec2d *a, const double f);
void
vec_apply(t_vec2d *a, double (*fn)(const double x));

#endif // VECTOR_H
