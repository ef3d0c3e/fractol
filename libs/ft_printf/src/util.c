/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf_args.h"
#include <unistd.h>

int	__printf_pad(int fd, char c, int width)
{
	int	i;

	i = 0;
	while (i < width)
	{
		write(fd, &c, 1);
		++i;
	}
	return ((width > 0) * width);
}

int	__printf_max(int x, int y)
{
	return ((x >= y) * x + (x < y) * y);
}

int	__printf_min(int x, int y)
{
	return ((x >= y) * y + (x < y) * x);
}

int	__printf_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

char	*__printf_strchr(const char *s, int c)
{
	while (*s != c)
	{
		if (!*s)
			return (0);
		++s;
	}
	return ((char *)s);
}
