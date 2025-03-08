/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "args.h"
#include <stdlib.h>
#include <ft_printf.h>

void	parse_positional(
	const char *program,
	const char *s,
	int *positional,
	t_pos *win_size)
{
	size_t	i;
	int		*num;

	if (*positional == 2)
	{
		ft_dprintf(2, "Error: Wrong number of positional parameters, expected: "
			"`WIDTH HEIGHT`\n");
		print_usage(program);
		exit(1);
	}
	i = 0;
	num = (int *)win_size + *positional;
	if (s[i] == '+')
		++i;
	*num = 0;
	while (s[i] >= '0' && s[i] <= '9')
		*num = *num * 10 + (s[i++] - '0');
	++*positional;
	if (*num < 256 || *num > 4096)
		exit((ft_dprintf(2, "Error: Expected sizes between 256 and 4096, "
					"got `%d` \n", *num), 1));
	if (!s[i])
		return ;
	ft_dprintf(2, "Error: Failed to parse window size '%s' as number\n", s);
	exit((print_usage(program), 1));
}

int
	parse_downsampling(const char *s)
{
	size_t	i;
	int		val;

	if (!s)
		exit((ft_dprintf(2, "Error: Downsampling expects an integer\n", s), 1));
	val = 0;
	i = 0;
	if (s[i] == '+')
		++i;
	while (s[i] >= '0' && s[i] <= '9')
		val = val * 10 + (s[i++] - '0');
	if (s[i])
		exit((ft_dprintf(2, "Error: Unexpected character in downsampling: "
					"`%s` \n", s), 1));
	if (val <= 0)
		exit((ft_dprintf(2, "Error: Downsampling expects a strictly positive "
					"integer, got `%d` \n", val), 1));
	return (val);
}

int
	parse_kernel(const char *s)
{
	size_t	i;
	int		val;

	if (!s)
		exit((ft_dprintf(2, "Error: Kernel id expects an integer parameter\n",
					s), 1));
	val = 0;
	i = 0;
	if (s[i] == '+')
		++i;
	while (s[i] >= '0' && s[i] <= '9')
		val = val * 10 + (s[i++] - '0');
	if (s[i])
		exit((ft_dprintf(2, "Error: Unexpected character in kernel id: `%s` \n",
					s), 1));
	if (val < 0)
		exit((ft_dprintf(2, "Error: Kernel id expects a positive integer, "
					"got `%d` \n", val), 1));
	return (val);
}
