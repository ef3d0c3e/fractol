#ifndef VIEWPORT_H
# define VIEWPORT_H

# include "ui.h"
# include "matrix.h"

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
	void	*data;
}	t_viewport;

t_viewport
viewport_create(
		t_pos size,
		t_vec2d(*screen_to_space)(const t_viewport *this, const t_pos pos),
		t_pos(*space_to_screen)(const t_viewport *this, const t_vec2d pos),
		void *data);

/**
 * @brief Moves the view
 */
void
view_move(
		t_viewport *this,
		const t_pos start,
		const t_pos end,
		const int zoom_delta);

/**
 * @brief Applies closure to each pixel in the viewport
 *
 * @param view Viewport to iterate over
 * @param callback Callback closyre
 * @param closure Closure data
 */
void
viewport_foreach(
		const t_viewport *this,
		void (*callback)(t_pos pos, t_vec2d z, void *data),
		void *closure);

#endif // VIEWPORT_H
