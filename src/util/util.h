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
#ifndef UTIL_H
# define UTIL_H

/**
 * @file Misc utilities
 */

# include <stdlib.h>

# ifdef __clang__

typedef char	t_char32 __attribute__((ext_vector_type(32), aligned(1)));
# else

typedef char	t_char32 __attribute__((vector_size(32), aligned(1)));
# endif // __clang__

/**
 * @brief Memcpy functin
 *
 * @note The bahaviour of this functyion is undefined if `[src, src+n]` overlaps
 * with `[dest, dest+n]`.
 *
 * @param dest Destination buffer
 * @param src Source buffer
 * @param n Number of bytes to copy from `src` into `dest`
 *
 * @returns `dest`
 */
void
*ft_memcpy(void *dest, const void *src, size_t n);
/**
 * @brief Strcmp function
 *
 * @param l First string
 * @param r Second string
 *
 * @returns 0 iff `l == r`, negative iff `l < r` and positive iff `l > r`
 */
int
ft_strcmp(const char *l, const char *r);
/**
 * @brief Realloc function
 *
 * @param ptr Buffer to realllocate
 * @param old Current size of the buffer
 * @param size New size of the buffer
 *
 * @retruns A buffer sufficiently large enough to hold size bytes, while copying
 * `old` bytes from the original pointer.
 */
void
*ft_realloc(void *ptr, const size_t old, const size_t size);

#endif // UTIL_H
