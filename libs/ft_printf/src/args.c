/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf_args.h"

/* A modified strcmp that modifies the first parameter */
static int	printf_equal(const char **a, const char *b)
{
	const char	*cpy;

	cpy = *a;
	while (*cpy && *b && *cpy == *b)
	{
		++cpy;
		++b;
	}
	if (!*b)
	{
		*a = cpy;
		return (1);
	}
	return (0);
}

int	__printf_process_arg(int fd, const char **s, va_list ap)
{
	struct s_printf_fmt	fmt;

	fmt = __printf_parse_fmt(s);
	if (printf_equal(s, "d") || printf_equal(s, "i"))
		return (__printf_print_int(fd, &fmt, va_arg(ap, int)));
	else if (printf_equal(s, "u"))
		return (__printf_print_unsigned(fd, &fmt, va_arg(ap, unsigned int)));
	else if (printf_equal(s, "c"))
		return (__printf_print_char(fd, &fmt, (unsigned char)va_arg(ap, int)));
	else if (printf_equal(s, "s"))
		return (__printf_print_string(fd, &fmt, va_arg(ap, const char *)));
	else if (printf_equal(s, "x"))
		return (__printf_print_hex(fd, &fmt, va_arg(ap, unsigned int), 0));
	else if (printf_equal(s, "X"))
		return (__printf_print_hex(fd, &fmt, va_arg(ap, unsigned int), 1));
	else if (printf_equal(s, "p"))
		return (__printf_print_ptr(fd, &fmt, va_arg(ap, void *)));
	return (0);
}
