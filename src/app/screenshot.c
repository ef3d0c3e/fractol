/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file BMP export capability!
 */

#include "ft_printf.h"
#include "mlx.h"
#include <app/fractol.h>
#include <fcntl.h>

/* Renders text by bypassing the draqueue */
static void	status(t_fractol *f, char *s)
{
	const int	x = f->ui.size.x * 0.05f;
	const int	y = 7 * f->ui.size.y / 8;

	mlx_string_put(f->mlx, f->window, x + 2, y + 2, 0x2f2f2f, s);
	f->mlx->do_flush = 1;
	mlx_string_put(f->mlx, f->window, x, y, 0xFFFFFF, s);
}

void
	fractol_screenshot(t_fractol *f)
{
	int				fd;
	size_t			i;
	const t_color	*data;
	char			buf[1024];
	size_t			size;

	fd = open("screenshot.ppm", O_CREAT | O_RDWR, 0777);
	if (fd < 0)
		exit((ft_dprintf(2, "Error: Failed to open `screenshot.ppm`\n"), 1));
	status(f, "Saving 'screenshot.ppm'...");
	ft_dprintf(fd, "P6\n%d %d\n255\n", f->ui.size.x, f->ui.size.y);
	i = 0;
	data = (t_color *)f->ui.render->data;
	size = 0;
	while (i++ < ((size_t)f->ui.size.x) * f->ui.size.y)
	{
		buf[size++] = (uint8_t)data[i - 1].channels.r;
		buf[size++] = (uint8_t)data[i - 1].channels.g;
		buf[size++] = (uint8_t)data[i - 1].channels.b;
		while (size + 3 >= sizeof(buf))
			size -= write(fd, buf, size);
	}
	write(fd, buf, size);
	close(fd);
	ft_printf("File 'screenshot.ppm' saved.\n");
}
