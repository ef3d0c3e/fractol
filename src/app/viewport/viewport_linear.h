/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_linear.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef VIEWPORT_LINEAR_H
# define VIEWPORT_LINEAR_H

/**
 * @file Linear viewport definition
 */

# include <app/viewport/viewport.h>

/**
 * @brief Data for the linear viewport
 */
struct s_viewport_linear_data
{
	/**
	 * @brief Transformation matrix
	 */
	t_mat2d	mat;
	/**
	 * @brief Inverse of the projection matrix
	 */
	t_mat2d	inv;
};

/**
 * @brief Creates the data for the linear viewport mapping module
 *
 * @param mat Transformation matrix
 *
 * @returns The data for the viewport module
 */
struct s_viewport_linear_data
view_linear_data(t_mat2d mat);

/**
 * @brief Linear transfor from screen coordinates to space coordinates
 *
 * @param this The viewport
 * @param pos Screen coordinates
 * @param delta Local delta for supersampling
 *
 * @returns Screen coordinates mapped to render space coordinates
 */
t_vec2d
view_linear_screen_to_space(
	const t_viewport *this,
	const t_vec2d pos);

/**
 * @brief Linear transfor from space coordinates to screen coordinates
 *
 * @param this The viewport
 * @param pos Space coordinates
 *
 * @returns Space coordinates mapped to screen coordinates
 */
t_pos
view_linear_space_to_screen(const t_viewport *this, const t_vec2d pos);

#endif // VIEWPORT_LINEAR_H
