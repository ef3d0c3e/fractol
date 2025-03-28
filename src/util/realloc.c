/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Realloc implementation
 */

#include "util.h"
#include <string.h>

void
	*ft_realloc(void *ptr, const size_t old, const size_t size)
{
	void	*new;

	if (old >= size)
		return (ptr);
	new = malloc(size);
	ft_memcpy(new, ptr, old);
	free(ptr);
	return (new);
}
