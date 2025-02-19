#include "image.h"
#include "mlx_int.h"

inline void	image_pixel(t_img *img, t_pos pos, uint32_t color)
{
	const int	factor = img->bpp / 8;

	img->data[(pos.x + pos.y * img->width) * factor] = color >> 16;
	img->data[(pos.x + pos.y * img->width) * factor + 1] = color >> 8;
	img->data[(pos.x + pos.y * img->width) * factor + 2] = color;
}

void	image_fill(t_img *img, uint32_t color)
{
	t_pos	pos;

	pos.y = 0;
	while (pos.y < img->height)
	{
		pos.x = 0;
		while (pos.x < img->width)
		{
			image_pixel(img, pos, color);
			++pos.x;
		}
		++pos.y;
	}
}
