#include "kernel.h"

static inline void iter(t_pos pos, t_vec2d z, const t_closure *data)
{
	int				i;
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
		x = x * x - y * y + z.x;
		y = 2 * tmp * y + z.y;

		if (x*x + y*y >= 4)
		{
			image_pixel(data->img, pos, 0xFF0000);
			return;
		}
		++i;
	}
	image_pixel(data->img, pos, 0x0000FF);
}

static inline void render(const struct s_viewport *viewport, t_img *img)
{
	struct s_kernel_closure closure;

	closure.img = img;
	closure.view = viewport;
	viewport_foreach(viewport, (void*)iter, &closure);
}

struct s_kernel mandel_ext_de = (struct s_kernel) {
	.name = "Mandelbrot Exterior Distance Estimate",
	.render = render
};
