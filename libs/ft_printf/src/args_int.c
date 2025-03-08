/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/28 15:26:46 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf_args.h"
#include <unistd.h>

static int	write_int(int fd, int x)
{
	int	written;

	written = 0;
	if (x >= 10 || x <= -10)
		written = write_int(fd, x / 10);
	return (written + __printf_print_char(fd, 0,
			(x % 10) * ((x >= 0) - (x < 0)) + '0'));
}

static int	log10i(int x)
{
	int	cnt;

	cnt = 0;
	while (x)
	{
		x /= 10;
		++cnt;
	}
	return (!cnt + cnt);
}

static char	get_sign(struct s_printf_fmt *fmt, int x)
{
	if (x < 0)
		return ('-');
	else if (fmt->force_sign)
		return ('+');
	else if (fmt->has_space)
		return (' ');
	return ('\0');
}

int	__printf_print_int(int fd, struct s_printf_fmt *fmt, int x)
{
	int		width;
	char	sign;
	int		w;

	width = log10i(x);
	sign = get_sign(fmt, x);
	w = 0;
	if (fmt->padding == PRINTF_PADDING_LEFT)
		w += __printf_pad(fd, ' ', fmt->width
				- __printf_max(width, fmt->precision) - (sign != 0));
	if (sign)
		w += write(fd, &sign, 1);
	w += __printf_pad(fd, '0', fmt->precision - width);
	if (fmt->padding == PRINTF_PADDING_ZEROS)
		w += __printf_pad(fd, '0', fmt->width - w - width);
	w += write_int(fd, x);
	w += __printf_pad(fd, ' ', fmt->width - w);
	return (w);
}
