#ifndef DRAW_BUFFER_H
# define DRAW_BUFFER_H

# include <mlx_int.h>
#include <stdint.h>

struct s_image
{
	t_img			*img;
	unsigned char	*data;
	int				bpp;
	int				len;
	int				endian;
};

void	set_pixel(struct s_image *img, size_t x, size_t y, uint32_t color_bgr);

#endif // DRAW_BUFFER_H
