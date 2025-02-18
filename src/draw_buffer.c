#include "draw_buffer.h"

void	image_pixel(struct s_image *img, t_pos pos, uint32_t color_bgr)
{
	const int	factor = img->bpp / 8;

	img->data[(pos.x + pos.y * img->len / factor) * factor] = color_bgr >> 16;
	img->data[(pos.x + pos.y * img->len / factor) * factor + 1] = color_bgr >> 8;
	img->data[(pos.x + pos.y * img->len / factor) * factor + 2] = color_bgr;
}
