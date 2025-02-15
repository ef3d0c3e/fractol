#include "../kernel.h"

static void iter(size_t x, size_t y, double re, double im, void *closure)
{
	
}

static void render(const struct s_viewport *viewport, struct s_image *img)
{
	struct s_kernel_closure closure;

	closure.img = img,
	closure.view = viewport,
	viewport_foreach(viewport, iter, &closure);
}

struct s_kernel mandel_ext_de = (struct s_kernel) {
	.name = "Mandelbrot Exterior Distance Estimate",
	.render = render
};
