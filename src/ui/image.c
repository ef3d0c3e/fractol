#include "image.h"

inline void	image_pixel(struct s_image *img, t_pos pos, uint32_t color_bgr)
{
	const int	factor = img->bpp / 8;

	img->data[(pos.x + pos.y * img->len / factor) * factor] = color_bgr >> 16;
	img->data[(pos.x + pos.y * img->len / factor) * factor + 1] = color_bgr >> 8;
	img->data[(pos.x + pos.y * img->len / factor) * factor + 2] = color_bgr;
}

void	image_fill(struct s_image *img, uint32_t color_bgr)
{
	t_pos	pos;

	pos.y = 0;
	while (pos.y < img->img->height)
	{
		pos.x = 0;
		while (pos.x < img->img->width)
		{
			image_pixel(img, pos, color_bgr);
			++pos.x;
		}
		++pos.y;
	}
}
