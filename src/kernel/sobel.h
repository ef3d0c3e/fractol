#ifndef SOBEL_H
#define SOBEL_H

# include <mlx_int.h>

/**
 * @brief Works in buffer
 *
 * @returns Address of buffer + size
 */
float	*sobel(t_img *img, float *buffer);

#endif // SOBEL_H
