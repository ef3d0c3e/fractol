/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf_args.h"
#include <unistd.h>

int	__printf_print_char(int fd, struct s_printf_fmt *fmt, unsigned char c)
{
	int	w;

	if (!fmt)
		return (write(fd, &c, 1));
	w = 0;
	if (fmt->padding != PRINTF_PADDING_RIGHT)
		w += __printf_pad(fd, ' ', fmt->width - 1);
	w += write(fd, &c, 1);
	w += __printf_pad(fd, ' ', fmt->width - w);
	return (w);
}
