/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "args.h"
#include <ft_printf.h>
#include <stdlib.h>

void	print_usage(const char *program)
{
	ft_dprintf(2, "Usage: %s [opts...] WIN_WIDTH WIN_HEIGHT\n", program);
}

void	print_help(const char *program)
{
	ft_dprintf(2, "\nfractol -- Fractal explorer program in C\n"
		"Copyright (c) 2025\n\n");
	print_usage(program);
	ft_dprintf(2, "\nOptions:\n"
		"  -h, --help\tShow this page\n"
		"  -v, --version\tVersion and license informations\n\n"
		"  -d, --downsample N\tDownsampling factor (default: 1)\n"
		"  --kernel ID\tInitial render kernel (default: 0)"
		"\nControls:\n"
		"> Mouse Left\tMoves the camera while held down\n"
		"> Mouse Wheel\tZooms at the cursor's location\n"
		"> Mouse Right\tSelect the Julia parameter at the current cursor\n"
		"\t\tlocation\n\n"
		"[R]\t\tRender the fractal for the current camera\n"
		"[U]\t\tUpsample an already rendered fractal\n"
		"[T]\t\tRe-render pixels with the default fractal's color\n\n"
		"[Q]\t\tIncrease the number of iterations\n"
		"[A]\t\tDecrease the number of iterations\n\n"
		"[S]\t\tToggle ui (toggles arrow key navigation)\n\n"
		"[F]\t\tRandomize colors\n"
		);
}

void	print_version(void)
{
	ft_dprintf(2, "\nfractol -- Fractal explorer program in C\n"
		"Copyright (c) 2025 - Lino Gamba\n\n"
		"version: 1.0\n\n"
		"fractol is licensed under the GNU General Public License version 3 "
		"(GPLv3)\nunder the terms of the Free Software Foundation "
		"<https://www.gnu.org/licenses/gpl-3.0.en.html>.\n\n"
		"This program is free software; you may modify and redistribute it.\n"
		"There is NO WARRANTY, to the extent permitted by law.\n");
}

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
	if (!s[i])
		return ;
	ft_dprintf(2, "Error: Failed to parse window size '%s' as " "number\n", s);
	if (*num < 256)
		exit((ft_dprintf(2, "Error: Expected sizes of at least `256x256`, got `%d` \n", *num), 1));
	if (*num > 4096)
		exit((ft_dprintf(2, "Error: Expected sizes of at most `4096`, got `%d` \n", *num), 1));
	print_usage(program);
	exit(1);
}

int
	parse_uint(const char *s)
{
	size_t	i;
	int		val;

	if (!s)
		exit((ft_dprintf(2, "Error: Expected integer parameter\n", s), 1));
	val = 0;
	i = 0;
	if (s[i] == '+')
		++i;
	while (s[i] >= '0' && s[i] <= '9')
		val = val * 10 + (s[i++] - '0');
	if (s[i])
		exit((ft_dprintf(2, "Error: Unexpected character in number: `%s` \n", s), 1));
	if (val < 0)
		exit((ft_dprintf(2, "Error: Expected positive integer, got `%d` \n", val), 1));
	return (val);
}
