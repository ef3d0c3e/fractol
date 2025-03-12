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

/**
 * @file Fractol entry point
 */

#include <args.h>
#include <util/util.h>
#include <app/fractol.h>

#include <ft_printf.h>
#include <stdbool.h>

static bool	parse_opts(int *i, char **argv, int *args)
{
	if (!ft_strcmp(argv[*i], "-h") || !ft_strcmp(argv[*i], "--help"))
		exit((print_help(argv[0]), 0));
	else if (!ft_strcmp(argv[*i], "-v") || !ft_strcmp(argv[*i], "--version"))
		exit((print_version(), 0));
	else if (!ft_strcmp(argv[*i], "-d") || !ft_strcmp(argv[*i], "--downsample"))
		args[0] = parse_downsampling(argv[++(*i)]);
	else if (!ft_strcmp(argv[*i], "--kernel"))
		args[1] = parse_kernel(argv[++(*i)]);
	else if (!ft_strcmp(argv[*i], "-o")
		|| !ft_strcmp(argv[*i], "--oversampling"))
		args[2] = parse_oversampling(argv[++(*i)]);
	else if (argv[*i][0] == '-')
		exit((ft_dprintf(2, "Error: Unrecognized parameter `%s`\n"
					"Try `--help` for help.\n", argv[*i]), 1));
	else
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_pos	win_size;
	int		i;
	int		positional;
	int		args[3];

	i = 0;
	positional = 0;
	args[0] = 1;
	args[1] = 0;
	args[2] = 1;
	while (++i < argc)
	{
		if (!parse_opts(&i, argv, args))
			parse_positional(argv[0], argv[i], &positional, &win_size);
	}
	if (positional != 2)
		exit((ft_dprintf(2, "Error: Wrong number of positional parameters, "
					"expected: `WIDTH HEIGHT`\n"), print_usage(argv[0]), 1));
	fractol_start(win_size, args[0], args[1], args[2]);
	return (0);
}
