/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <ft_printf.h>
#include "printf_args.h"
#include <unistd.h>

static int	_strlen(const char *s)
{
	if (s)
		return (__printf_strlen(s));
	return (__printf_strlen("(null)"));
}

int	__printf_print_string(int fd, struct s_printf_fmt *fmt, const char *s)
{
	int	w;
	int	width;

	if (!fmt && s)
		return (write(fd, s, _strlen(s)));
	else if (!fmt)
		return (write(fd, "(null)", 6));
	if (fmt->has_precision && (s || fmt->precision >= 6))
		width = __printf_min(_strlen(s), fmt->precision);
	else
		width = _strlen(s);
	w = 0;
	if (fmt->padding != PRINTF_PADDING_RIGHT)
		w += __printf_pad(fd, ' ', fmt->width
				- fmt->has_precision * __printf_min(width, fmt->precision)
				- !fmt->has_precision * width);
	if (s)
		w += write(fd, s, width);
	else if (!fmt->has_precision || fmt->precision >= 6)
		w += write(fd, &"(null)", 6);
	w += __printf_pad(fd, ' ', fmt->width - w);
	return (w);
}
/*
#include <stdio.h>
int main()
{
	printf("%d\n", ft_printf("|%+1u|\n", 15));
	printf("%d\n",   printf("|%+1u|\n", 15));

	//printf("%d\n", ft_printf("|%15.6s|\n", 0));
	//printf("%d\n",   printf("|%15.6s|\n", 0));

	//printf("%d\n", ft_printf("|%-15.6s|\n", 0));
	//printf("%d\n",   printf("|%-15.6s|\n", 0));

	//printf("%d\n", ft_printf("|%.5s|\n", 0));
	//printf("%d\n",   printf("|%.5s|\n", 0));
}*/
