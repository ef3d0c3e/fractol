/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_ptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf_args.h"
#include <unistd.h>

static int	write_hex(int fd, unsigned long long x)
{
	int	written;

	written = 0;
	if (x >= 16)
		written = write_hex(fd, x / 16);
	return (written + __printf_print_char(fd, 0,
			"0123456789abcdef"[(x % 16)]));
}

static int	log16u(void *p)
{
	unsigned long long	x;
	int					cnt;

	x = (unsigned long long)p;
	if (!x)
		return (__printf_strlen("(nil)"));
	cnt = 0;
	while (x)
	{
		x /= 16;
		++cnt;
	}
	return (!cnt + cnt);
}

static char	get_sign(struct s_printf_fmt *fmt)
{
	if (fmt->force_sign)
		return ('+');
	else if (fmt->has_space)
		return (' ');
	return ('\0');
}

int	__printf_print_ptr(
		int fd,
		struct s_printf_fmt *fmt,
		void *p
		)
{
	int		width;
	int		w;
	char	sign;

	width = log16u(p) + 2 * ((unsigned long long)p != 0);
	sign = get_sign(fmt);
	w = 0;
	if (fmt->padding != PRINTF_PADDING_RIGHT && (!fmt->has_precision || !p))
		w += __printf_pad(fd, ' ', fmt->width - width - (!!p) * (sign != 0));
	if (p)
	{
		if (sign)
			w += write(fd, &sign, 1);
		w += write(fd, "0x", 2);
		if (fmt->has_precision)
			w += __printf_pad(fd, '0', fmt->precision - width
					- (!!p) * (sign != 0) + 2);
		w += write_hex(fd, (unsigned long long)p);
	}
	else
		w += write(fd, "(nil)", 5);
	w += __printf_pad(fd, ' ', fmt->width - w);
	return (w);
}
