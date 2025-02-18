#ifndef IMAGE_H
# define IMAGE_H

# include "ui.h"
# include <mlx_int.h>
# include <stdint.h>

/**
 * @brief Sets the pixel of an image at a given position
 *
 * @param img Image
 * @param pos Position of pixel to set
 * @param color_bgr Color in B:G:R 8bpc format
 */
void	image_pixel(t_img *img, t_pos pos, uint32_t color_bgr);

/**
 * @brief Fills the image with solid color
 *
 * @param img Image to fill
 * @param color_bgr Color in B:G:R 8bpc format
 */
void	image_fill(t_img *img, uint32_t color_bgr);

#endif // IMAGE_H
