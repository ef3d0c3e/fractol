#ifndef SFX_H
# define SFX_H

# include "draw_buffer.h"

/**
 * @brief Renders components to a separate image to display on top
 */
typedef struct s_sfx
{
	/**
	 * @brief Rendered pixels
	 */
	t_img		*render;
	/**
	 * @brief Overlay
	 */
	t_img		*overlay;

	size_t		queue_size;
	size_t		queue_capacity;
	t_sfx_item	*queue;
}	t_sfx;

/**
 * @brief Create a new special effect
 */
t_sfx
sfx_new(const t_fractol *f, const t_pos size);
/**
 * @brief Delete a special effect
 */
void
sfx_free(const t_fractol *f, t_sfx *sfx);
/**
 * @brief Display a and (re)-render the overlay
 */
void
sfx_display(const t_fractol *fractol, const t_sfx *sfx);

/**
 * @brief Draws in raster
 */
void
sfx_draw(t_sfx *sfx, t_sfx_item item);

#endif // SFX_H
