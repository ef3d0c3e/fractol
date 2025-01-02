#ifndef DRAW_BUFFER_H
#define DRAW_BUFFER_H

#include "../minilibx-linux/mlx_int.h"
#include <stdlib.h>

struct s_image
{
	t_img			img;
	unsigned char	*data;
	int				bpp;
	int				len;
	int				endian;
};

struct s_draw_buffer
{
	size_t			x;
	size_t			y;
	struct s_image	front;
};

#endif // DRAW_BUFFER_H
