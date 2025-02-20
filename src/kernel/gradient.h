/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GRADIENT_H
# define GRADIENT_H

# include <kernel/color.h>
# include <stdint.h>
# include <stdlib.h>

/**
 * @brief Color with weight
 */
struct s_gr_color
{
	t_color color;
	float	weight;
};

/**
 * @brief A color gradient
 */
typedef struct s_gradient
{
	/**
	 * @brief Number of colored pixels
	 */
	size_t		size;
	/**
	 * @brief Color data
	 */
	t_color		*colors;
}	t_gradient;

/**
 * @brief Creates a new gradient
 *
 * To make the gradient repeat continuously, specify the first color as the last color.
 * This function will generate a 4096 wide gradient that can be picked from later.
 *
 * @param colors The colors array
 * @param size The number of colors
 *
 * @returns The new gradient
 */
t_gradient
gradient_new(const struct s_gr_color *colors, size_t size);
/**
 * @brief Frees a gradient
 *
 * @param g Gradient to free
 */
void
gradient_free(t_gradient *g);
/**
 * @brief Pick a color on the gradient
 *
 * The gradient space is compressed to [0, 1];
 *
 * @param g The gradient
 * @param f Point in the gradient to pick.
 *
 * @returns The color
 */
t_color
gradient_get(const t_gradient *g, float f);

#endif // GRADIENT_H
