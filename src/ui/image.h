/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef IMAGE_H
# define IMAGE_H

/**
 * @file MLX image related capabilities
 */
# include "ui.h"
# include <mlx_int.h>

# include <stdint.h>

/**
 * @brief Sets the pixel of an image at a given position
 *
 * @param img Image
 * @param pos Position of pixel to set
 * @param color Color in R:G:B 8bpc format
 */
void	image_pixel(t_img *img, t_pos pos, uint32_t color);

/**
 * @brief Fills the image with solid color
 *
 * @param img Image to fill
 * @param color Color in B:G:R 8bpc format
 */
void	image_fill(t_img *img, uint32_t color);

#endif // IMAGE_H
