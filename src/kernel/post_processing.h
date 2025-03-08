/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_processing.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef POST_PROCESSING_H
# define POST_PROCESSING_H

# include <kernel/color.h>
# include <util/pos.h>
# include <mlx_int.h>

/**
 * @brief Sobel edge detection filter
 *
 * @param in Input buffer
 * @param line_length Length of the line
 * @param pos Position in the buffer: `pos.x + pos.y * line_length`
 *
 * @returns The sobel kernel evaluated at pos
 */
float
postprocess_sobel(float *in, size_t line_length, t_pos pos);

/**
 * @brief Sobel edge detection filter
 *
 * @param in Input buffer
 * @param line_length Length of the line
 * @param pos Position in the buffer: `pos.x + pos.y * line_length`
 *
 * @returns The sobel kernel evaluated at pos
 */
float
postprocess_gauss_blur_5(float *in, size_t line_length, t_pos pos);

/**
 * @brief Performs bicubic interpolation
 *
 * @param in Input image
 * @param in_size Pixel sizes of input image
 * @param out Output image
 * @param out_size Pixel sizes of output image
 */
void
postprocess_bicubic(
	const t_color *in,
	t_pos in_size,
	t_color *out,
	t_pos out_size);

/**
 * @brief Performs bilinear interpolation
 *
 * @param in Input image
 * @param in_size Pixel sizes of input image
 * @param out Output image
 * @param out_size Pixel sizes of output image
 */
void
postprocess_bilinear(
	const t_color *in,
	t_pos in_size,
	t_color *out,
	t_pos out_size);

/**
 * @brief Performs edge detection then blurring.
 *
 * The result of this function is a float array which contains weights to use
 * for supersampling. The filter is applied to the input `img` parameter
 *
 * @param img Input image to apply the filter to
 * @param in An array large enough to contain at least twice the number of
 * pixels as floats. E.g: `2 * WIDTH * HEIGHT * sizeof(float)`
 *
 * @returns Upsampling weights for each screen pixels
 */
float	*postprocess_edge_filter(t_img *img, float *in);

/**
 * @brief Postprocess for upscaling
 *
 * The output buffer of this function needs to be used to know which pixels
 * need re-rendering
 *
 * @param img Input image to apply the filter to
 * @param in An array large enough to contain at least twice the number of
 * pixels as floats. E.g: `2 * WIDTH * HEIGHT * sizeof(float)`
 *
 * @returns Upsampling weights for each screen pixels
 */
float	*postprocess_upscale(t_img *img, t_pos size, t_color *in);

#endif // SOBEL_H
