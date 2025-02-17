#include "draw_buffer.h"

void	set_pixel(struct s_image *img, size_t x, size_t y, uint32_t color_bgr)
{
	const size_t	factor = img->bpp / 8;

	img->data[(x + y * img->len / factor) * factor] = color_bgr >> 16;
	img->data[(x + y * img->len / factor) * factor + 1] = color_bgr >> 8;
	img->data[(x + y * img->len / factor) * factor + 2] = color_bgr;
}
