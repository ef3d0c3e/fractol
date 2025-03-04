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
# include <stdbool.h>

/**
 * @brief Viewport for rendering
 *
 * This maps screen coordinates to render coordinates and vice versa.
 * Sadly using integers for screen coordinates was a mistake because they incur
 * precision loss.
 */
typedef struct s_viewport
{
	/**
	 * @brief Screen size
	 */
	t_pos		size;
	/**
	 * @brief Viewport dimensions
	 */
	t_mat2d		view;
	/**
	 * @brief View function
	 */
	t_vec2d	(*screen_to_space)(const struct s_viewport * this, const t_pos pos,
		const t_vec2d delta);
	t_pos	(*space_to_screen)(const struct s_viewport * this,
		const t_vec2d pos);
	void		*data;
}	t_viewport;

t_viewport
viewport_create(
	t_pos size,
	t_vec2d(*screen_to_space)(const t_viewport *this, const t_pos pos,
		const t_vec2d delta),
	t_pos(*space_to_screen)(const t_viewport *this, const t_vec2d pos),
	void *data);

void
viewport_free(t_viewport *this);

/**
 * @brief Moves the view
 */
void
view_move(
	t_viewport *this,
	const t_vec2d start,
	const t_vec2d end,
	const double factor);
void
view_zoom(
	t_viewport *this,
	const t_vec2d center,
	const int zoom);

/**
 * @brief Data passed to the fragment shader processor
 */
struct s_fragment_data
{
	/**
	 * @brief Fragment viewport
	 */
	const t_viewport	*viewport;
	/**
	 * @brief Default background color
	 */
	t_color				dafault_color;
	/**
	 * @brief Draw buffer
	 */
	t_img				*img;
	/**
	 * @brief Array containing resampling weights for each pixels.
	 * NULL for none
	 */
	float				*oversampling_data;
	/**
	 * @brief Indicates the processor to only recompute black pixels
	 */
	bool				post_pass;
};

/**
 * @brief Applies closure to each pixel in the viewport
 *
 * @param data Viewport data to iterate over
 * @param shader Callback closyre
 * @param closure Closure data
 */
void
viewport_fragment(
	struct s_fragment_data *data,
	t_color (*shader)(double _Complex z, void *data),
	void *closure);

#endif // VIEWPORT_H
