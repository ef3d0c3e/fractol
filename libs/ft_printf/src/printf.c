/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf_args.h"
#include <unistd.h>

int	ft_vprintf(const char *fmt, va_list pa)
{
	int			printed;
	const char	*n;
	const char	*p;

	printed = 0;
	p = fmt;
	while (1)
	{
		n = __printf_strchr(p, '%');
		if (!n)
			return (printed + __printf_print_string(1, 0, p));
		else if (n[1] == '%')
		{
			printed += write(1, p, n - p) + write(1, "%", 1);
			p = n + 2;
		}
		else
		{
			printed += write(1, p, n - p);
			p = n + 1;
			printed += __printf_process_arg(1, &p, pa);
		}
	}
	return (printed);
}

int	ft_printf(const char *fmt, ...)
{
	va_list		args;
	int			printed;

	va_start(args, fmt);
	printed = ft_vprintf(fmt, args);
	va_end(args);
	return (printed);
}

int	ft_vdprintf(int fd, const char *fmt, va_list pa)
{
	int			printed;
	const char	*n;
	const char	*p;

	printed = 0;
	p = fmt;
	while (1)
	{
		n = __printf_strchr(p, '%');
		if (!n)
			return (printed + __printf_print_string(fd, 0, p));
		else if (n[1] == '%')
		{
			printed += write(fd, p, n - p) + write(fd, "%", 1);
			p = n + 2;
		}
		else
		{
			printed += write(fd, p, n - p);
			p = n + 1;
			printed += __printf_process_arg(fd, &p, pa);
		}
	}
	return (printed);
}

int	ft_dprintf(int fd, const char *fmt, ...)
{
	va_list		args;
	int			printed;

	va_start(args, fmt);
	printed = ft_vdprintf(fd, fmt, args);
	va_end(args);
	return (printed);
}
