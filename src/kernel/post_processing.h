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

# include <mlx_int.h>

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
 * @returns Address of `in + img_size`
 */
float	*postprocess_edge_filter(t_img *img, float *in);

#endif // SOBEL_H
