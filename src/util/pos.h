/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef POS_H
# define POS_H

/**
 * @brief Screen position structure
 */
typedef struct s_pos
{
	/**
	 * @brief X-coordinate
	 */
	int	x;
	/**
	 * @brief Y-coordinate
	 */
	int	y;
}	t_pos;

#endif // POS_H
