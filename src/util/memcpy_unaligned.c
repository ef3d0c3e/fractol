/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy_unaligned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Memcpy for unaligned pointers
 */

#include <stdlib.h>

void
	*ft_memcpy_unaligned(void *dest, const void *src, size_t len)
{
	char		*d;
	const char	*s = (const char *)src;

	d = (char *)dest;
	while (len > 0)
	{
		*d = *s;
		++d;
		++s;
		--len;
	}
	return (dest);
}
