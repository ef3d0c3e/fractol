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

/**
 * @file Basic argument handlers
 */

#include <args.h>

#include <ft_printf.h>

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
		"  --kernel ID\tInitial render kernel (default: 0)\n"
		"  -o, --oversampling N\tOversampling amount for upsampling"
		" (default: 1)\n\nControls:\n"
		"> Mouse Left\tMoves the camera while held down\n"
		"> Arrow keys\t(if selector is off) Moves the camera\n\n"
		"> Mouse Wheel\tZooms at the cursor's location\n"
		"> '+' or '-'\tZooms at the view's center\n\n"
		"> Mouse Right\tSelect the Julia parameter at the current cursor\n"
		"\t\tlocation\n\n"
		"[R]\t\tRender the fractal for the current camera\n"
		"[U]\t\tUpsample an already rendered fractal\n"
		"[T]\t\tRe-render pixels with the default fractal's color\n\n"
		"[Q]\t\tIncrease the number of iterations\n"
		"[A]\t\tDecrease the number of iterations\n\n"
		"[S]\t\tToggle ui (toggles arrow key navigation)\n\n"
		"[F]\t\tRandomize colors\n"
		"[Z]\t\tSave raster to 'screenshot.ppm'\n"
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
