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

// memcpy based on https://github.com/nadavrot/memset_benchmark
#include "util.h"
#include <stdint.h>

static inline void	*memcpy_4(char *dest, const char *src, size_t n)
{
	const char	*s = (char *)src;
	char		*d;

	d = (char *)dest;
	if (n == 0)
		return (dest);
	d[0] = s[0];
	d[n - 1] = s[n - 1];
	if (n <= 2)
		return (dest);
	d[1] = s[1];
	d[2] = s[2];
	return (dest);
}

static inline void	*memcpy_16(char *dest, const char *src, size_t n)
{
	const char	*first_s = src;
	const char	*last_s = (char *)src + n - 8;
	char		*first_d;
	char		*last_d;

	first_d = dest;
	last_d = dest + n - 8;
	if (n >= 8)
	{
		*((uint64_t *)first_d) = *((uint64_t *)first_s);
		*((uint64_t *)last_d) = *((uint64_t *)last_s);
		return (dest);
	}
	last_s = src + n - 4;
	last_d = dest + n - 4;
	*((uint32_t *)first_d) = *((uint32_t *)first_s);
	*((uint32_t *)last_d) = *((uint32_t *)last_s);
	return (dest);
}

static inline void	*memcpy_32(void *dest, const void *src, size_t n)
{
	const char	*first_s = src;
	const char	*last_s = (char *)src + n - 16;
	char		*first_d;
	char		*last_d;

	first_d = dest;
	last_d = (char *)dest + n - 16;
	*((uint16_t *)first_d) = *((uint16_t *)first_s);
	*((uint16_t *)last_d) = *((uint16_t *)last_s);
	return (dest);
}

void
	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*s = src;
	const char	*last_word_s = s + n - 32;
	char		*d;
	char		*last_word_d;

	d = dest;
	last_word_d = d + n - 32;
	if (n <= 4)
		return (memcpy_4(dest, src, n));
	else if (n <= 16)
		return (memcpy_16(dest, src, n));
	else if (n <= 32)
		return (memcpy_32(dest, src, n));
	*((t_char32 *)d) = *((t_char32 *)s);
	d += 32;
	s += 32;
	while (d < last_word_d)
	{
		*((t_char32 *)d) = *((t_char32 *)s);
		d += 32;
		s += 32;
	}
	*((t_char32 *)last_word_d) = *((t_char32 *)last_word_s);
	return (dest);
}
