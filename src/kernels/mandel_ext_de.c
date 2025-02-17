#include "../kernel.h"
#include <stdio.h>

static inline void iter(size_t ix, size_t iy, double re, double im, void *closure)
{
	const t_closure	*data = closure;
	size_t			i;
	double			x;
	double			y;
	double			tmp;
	
	x = 0;
	y = 0;
	tmp = 0;
	i = 0;
	while (i < 100)
	{
		tmp = x;
		x = x * x - y * y + re;
		y = 2 * tmp * y * im;

		if (x*x + y*y >= 4)
		{
			set_pixel(data->img, ix, iy, 0xFF0000);
			return;
		}
		++i;
	}
	set_pixel(data->img, ix, iy, 0x0000FF);
}

static inline void render(const struct s_viewport *viewport, struct s_image *img)
{
	struct s_kernel_closure closure;

	closure.img = img;
	closure.view = viewport;
	viewport_foreach(viewport, iter, &closure);
}

struct s_kernel mandel_ext_de = (struct s_kernel) {
	.name = "Mandelbrot Exterior Distance Estimate",
	.render = render
};
