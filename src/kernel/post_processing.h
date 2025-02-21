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
 * @brief Performs sobel filter with a 3x3 gaussian blu.
 *
 * Requires in to be able to hold 2 * (4 bytes) * img_size
 *
 * 
 * @returns Address of buffer + img_size
 */
float	*sobel(t_img *img, float *in);

#endif // SOBEL_H
