/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_unsigned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf_args.h"
#include <unistd.h>

static int	write_int(int fd, unsigned int x)
{
	int	written;

	written = 0;
	if (x >= 10)
		written = write_int(fd, x / 10);
	return (written + __printf_print_char(fd, 0,
			(x % 10) + '0'));
}

static int	log10u(unsigned int x, struct s_printf_fmt *fmt)
{
	int	cnt;

	if (!x && fmt->has_precision)
		return (__printf_strlen("(null)"));
	cnt = 0;
	while (x)
	{
		x /= 10;
		++cnt;
	}
	return (!cnt + cnt);
}

int	__printf_print_unsigned(int fd, struct s_printf_fmt *fmt, unsigned int x)
{
	int		width;
	int		w;

	width = log10u(x, fmt);
	w = 0;
	if (fmt->padding == PRINTF_PADDING_LEFT)
		w += __printf_pad(fd, ' ', fmt->width
				- __printf_max(width, fmt->precision));
	if (!fmt->has_precision || x)
		w += __printf_pad(fd, '0', fmt->precision - width);
	if (fmt->padding == PRINTF_PADDING_ZEROS)
		w += __printf_pad(fd, '0', fmt->width - w - width);
	if (fmt->has_precision && !x)
	{
		if (fmt->precision == 0)
			width = write(fd, "(null)", 6);
		else
			w += __printf_pad(fd, '0', fmt->precision);
	}
	else
		w += write_int(fd, x);
	w += __printf_pad(fd, ' ', fmt->width - w);
	return (w);
}
