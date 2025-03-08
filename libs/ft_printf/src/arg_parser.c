/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf_args.h"
#include <stddef.h>

/* Get a zeroed fmt */
static struct s_printf_fmt	fmt_new(void)
{
	size_t				i;
	struct s_printf_fmt	fmt;

	i = 0;
	while (i < sizeof(fmt))
		((char*)&fmt)[i++] = 0;
	return (fmt);
}

/* Parse the flags values and the width */
static void	parse_flags_and_width(const char **s, struct s_printf_fmt *fmt)
{
	while (1)
	{
		if (**s == '#' && ++(*s))
			fmt->alternate_form = 1;
		else if (**s == '0' && ++(*s) && fmt->padding != PRINTF_PADDING_RIGHT)
			fmt->padding = PRINTF_PADDING_ZEROS;
		else if (**s == '-' && ++(*s))
			fmt->padding = PRINTF_PADDING_RIGHT;
		else if (**s == ' ' && ++(*s))
			fmt->has_space = 1;
		else if (**s == '+' && ++(*s))
			fmt->force_sign = 1;
		else
			break ;
	}
	while (**s >= '0' && **s <= '9')
	{
		fmt->width = fmt->width * 10 + **s - '0';
		++(*s);
	}
}

static void	parse_precision(const char **s, struct s_printf_fmt *fmt)
{
	if (**s != '.')
		return ;
	++(*s);
	while (**s >= '0' && **s <= '9')
	{
		fmt->precision = fmt->precision * 10 + **s - '0';
		++(*s);
	}
	if (fmt->precision < 0)
		fmt->precision = 0;
	fmt->has_precision = 1;
	if (fmt->padding == PRINTF_PADDING_ZEROS)
		fmt->padding = PRINTF_PADDING_LEFT;
}

struct s_printf_fmt	__printf_parse_fmt(const char **s)
{
	struct s_printf_fmt	fmt;

	fmt = fmt_new();
	parse_flags_and_width(s, &fmt);
	parse_precision(s, &fmt);
	return (fmt);
}
