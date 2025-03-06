/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "util/pos.h"
#include "util/util.h"
#include <app/fractol.h>

static void	print_usage(const char *program)
{
	dprintf(2, "Usage: %s [opts...] WIN_WIDTH WIN_HEIGHT\n", program);
}

static void	print_help(const char *program)
{
	dprintf(2, "\nfractol -- Fractal explorer program in C\n"
		"Copyright (c) 2025\n\n");
	print_usage(program);
	dprintf(2, "\nOptions:\n"
		"  -h, --help	Show this page\n"
		"  -v, --version	Version and license informations\n"
		"\nControls:\n"
		"> Mouse Left\tMoves the camera while held down\n"
		"> Mouse Wheel\tZooms at the cursor's location\n"
		"> Mouse Right\tSelect the Julia parameter at the current cursor\n"
		"\t\tlocation\n"
		"[G]\t\t\n\n"
		"[R]\t\tRender the fractal for the current camera\n"
		"[U]\t\tUpsample an already rendered fractal\n"
		"[T]\t\tRe-render pixels with the default fractal's color\n\n"
		"[Q]\t\tIncrease the number of iterations\n"
		"[A]\t\tDecrease the number of iterations\n\n"
		"[S]\t\tToggle ui (toggles arrow key navigation)\n\n"
		"[F]\t\tRandomize colors\n"
		"[N]\t\tRandomize colors\n"
		);
}

static void	print_version(void)
{
	dprintf(2, "\nfractol -- Fractal explorer program in C\n"
		"Copyright (c) 2025 - Lino Gamba\n\n"
		"version: 1.0\n\n"
		"fractol is licensed under the GNU General Public License version 3 "
		"(GPLv3)\nunder the terms of the Free Software Foundation "
		"<https://www.gnu.org/licenses/gpl-3.0.en.html>.\n\n"
		"This program is free software; you may modify and redistribute it.\n"
		"There is NO WARRANTY, to the extent permitted by law.\n");
}

static void	parse_positional(
	const char *program,
	const char *s,
	int *positional,
	t_pos *win_size)
{
	size_t	i;
	int		*num;

	if (*positional == 2)
	{
		dprintf(2, "Error: Wrong number of positional parameters, expected: "
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
	dprintf(2, "Error: Failed to parse window size '%s' as " "number\n", s);
	print_usage(program);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_pos	win_size;
	int		i;
	int		positional;

	i = 0;
	positional = 0;
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], "-h") || !ft_strcmp(argv[i], "--help"))
			exit((print_help(argv[0]), 0));
		else if (!ft_strcmp(argv[i], "-v") || !ft_strcmp(argv[i], "--version"))
			exit((print_version(), 0));
		else if (argv[i][0] == '-')
			exit((dprintf(2, "Error: Unrecognized parameter `%s`\n"
						"Try `--help` for help.\n", argv[i]), 1));
		else
			parse_positional(argv[0], argv[i], &positional, &win_size);
	}
	if (positional != 2)
		exit((dprintf(2, "Error: Wrong number of positional parameters, "
					"expected: `WIDTH HEIGHT`\n"), print_usage(argv[0]), 1));
	fractol_start(win_size);
	return (0);
}
