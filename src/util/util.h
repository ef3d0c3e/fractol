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

# include <stdlib.h>

# ifdef __clang__

typedef char	t_char32 __attribute__((ext_vector_type(32), aligned(1)));
# else

typedef char	t_char32 __attribute__((vector_size(32), aligned(1)));
# endif // __clang__

void
*ft_memcpy(void *dest, const void *src, size_t n);
void
*ft_realloc(void *ptr, const size_t old, const size_t size);

#endif // UTIL_H
