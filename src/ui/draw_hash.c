/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Provides hashing for all draw items
 */

#include "util/util.h"
#include <ui/draw.h>

/* Computes the hash of a draw item */
uint32_t	draw_hash(const t_draw_item *item, uint32_t seed)
{
	static const size_t lengths[] = {
		[DRAW_RECT] = sizeof(struct s_draw_rect),
		[DRAW_TEXT] = sizeof(struct s_draw_text),
		[DRAW_TEXT_SHADOW] = sizeof(struct s_draw_text_shadow),
	};

	return (murmumr3_32((const void *)&item->draw, lengths[item->item], seed));
}
