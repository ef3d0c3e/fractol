#ifndef DRAW_BUFFER_H
# define DRAW_BUFFER_H

# include "ui.h"
# include <mlx_int.h>
# include <stdint.h>

struct s_image
{
	t_img			*img;
	unsigned char	*data;
	int				bpp;
	int				len;
	int				endian;
};

/**
 * @brief Sets the pixel of an image at a given position
 *
 * @param img Image
 * @param pos Position of pixel to set
 * @param color_bgr Color in B:G:R 8bpc format.
 */
void	image_pixel(struct s_image *img, t_pos pos, uint32_t color_bgr);

#endif // DRAW_BUFFER_H
