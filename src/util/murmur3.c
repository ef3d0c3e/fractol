/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Murmur3 implementation based on this:
 * https://en.wikipedia.org/wiki/MurmurHash#Algorithm
 */

#include <util/util.h>

static inline uint32_t
	murmur_32_scramble(uint32_t k)
{
	k *= 0xcc9e2d51;
	k = (k << 15) | (k >> 17);
	k *= 0x1b873593;
	return (k);
}

uint32_t
	murmumr3_32(const unsigned char *data, size_t len, uint32_t seed)
{
	uint32_t	h;
	uint32_t	k;
	size_t		i;

	h = seed;
	i = len >> 2;
	while (i-- != 0)
	{
		ft_memcpy(&k, data, sizeof(uint32_t));
		data += sizeof(uint32_t);
		h ^= murmur_32_scramble(k);
		h = (h << 13) | (h >> 19);
		h = h * 5 + 0xe6546b64;
	}
	k = 0;
	i = len & 3;
	while (i-- != 0)
	{
		k <<= 8;
		k |= data[i];
	}
	h ^= murmur_32_scramble(k);
	h = ((h ^ len) ^ ((h ^ len) >> 16)) * 0x85ebca6b;
	h = (h ^ (h >> 13)) * 0xc2b2ae35;
	return (h ^ (h >> 16));
}
