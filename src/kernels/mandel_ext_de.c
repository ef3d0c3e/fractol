#include "../kernel.h"

static void render(const struct s_viewport *viewport, struct s_image *img)
{
	int	x;
	int	y;

	while ()
	{

	}
}

struct s_kernel mandel_ext_de = (struct s_kernel) {
	.name = "Mandelbrot Exterior Distance Estimate",
	.render = render
};
