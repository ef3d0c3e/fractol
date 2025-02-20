/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef VIEWPORT_H
# define VIEWPORT_H

# include <util/math.h>
# include <kernel/color.h>
# include <mlx_int.h>

typedef struct s_viewport
{
	/**
	 * @brief Screen size
	 */
	t_pos	size;
	/**
	 * @brief Viewport dimensions
	 */
	t_mat2d	view;
	/**
	 * @brief View function
	 */
	t_vec2d(*screen_to_space)(const struct s_viewport *this, const t_pos pos);
	t_pos(*space_to_screen)(const struct s_viewport *this, const t_vec2d pos);
	const void	*data;
}	t_viewport;

t_viewport
viewport_create(
		t_pos size,
		t_vec2d(*screen_to_space)(const t_viewport *this, const t_pos pos),
		t_pos(*space_to_screen)(const t_viewport *this, const t_vec2d pos),
		const void *data);

void
viewport_free(t_viewport *this);

/**
 * @brief Moves the view
 */
void
view_move(
		t_viewport *this,
		const t_pos start,
		const t_pos end,
		const double factor);
void
view_zoom(
	t_viewport *this,
	const t_vec2d center,
	const int zoom);

/**
 * @brief Applies closure to each pixel in the viewport
 *
 * @param view Viewport to iterate over
 * @param callback Callback closyre
 * @param closure Closure data
 */
void
viewport_fragment(
		const t_viewport *this,
		t_img *img,
		t_color (*callback)(t_pos pos, t_vec2d z, void *data),
		void *closure);

#endif // VIEWPORT_H
