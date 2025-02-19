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
# include <ui/ui.h>
# include <kernel/color.h>
# include <mlx_int.h>

/**
 * @brief Sets the pixel of an image at a given position
 *
 * @param img Image
 * @param pos Position of pixel to set
 * @param color Color in R:G:B 8bpc format
 */
void	image_pixel(t_img *img, t_pos pos, t_color color);

/**
 * @brief Fills the image with solid color
 *
 * @param img Image to fill
 * @param color Color in B:G:R 8bpc format
 */
void	image_fill(t_img *img, t_color color);

#endif // IMAGE_H
