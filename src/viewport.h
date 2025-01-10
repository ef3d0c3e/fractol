#ifndef VIEWPORT_H
#define VIEWPORT_H

struct s_viewport
{
	double	cx;
	double	cy;
	double	zoom;

	int		sz_x;
	int		sz_y;

	/**
	 * @brief Anti-aliasing (MSAA)
	 */
	int aa;
};

struct s_viewport	viewport_create(int sz_x, int sz_y);

/**
 * @brief Applies closure to each pixel in the viewport
 *
 * @param view Viewport to iterate over
 * @param callback Callback closyre
 * @param closure Closure data
 */
void viewport_foreach(
		const struct s_viewport *view,
		void (*callback)(int x, int y, double zr, double zi, void*),
		void *closure);

#endif // VIEWPORT_H
