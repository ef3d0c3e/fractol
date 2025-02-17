#ifndef VIEWPORT_H
# define VIEWPORT_H

# include <stdlib.h>

#define OMP_KERN _Pragma("omp parallel")

typedef struct s_viewport
{
	double	cx;
	double	cy;
	double	zoom;

	size_t		sz_x;
	size_t		sz_y;

	/**
	 * @brief Anti-aliasing (MSAA)
	 */
	size_t aa;
}	t_viewport;

struct s_viewport	viewport_create(size_t sz_x, size_t sz_y);

/**
 * @brief Applies closure to each pixel in the viewport
 *
 *   <----- sz_x ----->
 *  ^
 *  |
 *  |
 * sz_y   (cx, cy)
 *  |
 *  |
 *  v
 *
 * @param view Viewport to iterate over
 * @param callback Callback closyre
 * @param closure Closure data
 */
void viewport_foreach(
		const struct s_viewport *view,
		void (*callback)(size_t x, size_t y, double zr, double zi, void*),
		void *closure);

#endif // VIEWPORT_H
