/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel_ext_de.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "kernel/color.h"
#include <kernel/kernel.h>
#include <complex.h>

static inline void hsv2rgb(double h, double s, double v, uint8_t *red, uint8_t *grn, uint8_t *blu) {
  double i, f, p, q, t, r, g, b;
  int ii;
  if (s == 0.0) { r = g = b = v; } else {
    h = 6 * (h - floor(h));
    ii = i = floor(h);
    f = h - i;
    p = v * (1 - s);
    q = v * (1 - (s * f));
    t = v * (1 - (s * (1 - f)));
    switch(ii) {
      case 0: r = v; g = t; b = p; break;
      case 1: r = q; g = v; b = p; break;
      case 2: r = p; g = v; b = t; break;
      case 3: r = p; g = q; b = v; break;
      case 4: r = t; g = p; b = v; break;
      default:r = v; g = p; b = q; break;
    }
  }
  *red = fmin(fmax(255 * r + 0.5, 0), 255);
  *grn = fmin(fmax(255 * g + 0.5, 0), 255);
  *blu = fmin(fmax(255 * b + 0.5, 0), 255);
}

static inline t_color iter(t_pos pos, t_vec2d c, const t_closure *data)
{
	int				i;
	const double _Complex cc = *(double _Complex *)&c;
	double _Complex z;
	double _Complex dz;
	const double ratio = (data->view->view.data[1] - data->view->view.data[0]) / (data->view->size.x / 2.0);

	z = 0;
	dz = 1;
	double k = 0;
	i = 0;
	while (i < data->max_it)
	{
		dz = 2 * dz * z + 1;
		z = z * z + cc;
		double m = cabs(z);
		k += exp(-m);
		if (m >= 1e8)
		{
			// color
			double hue = 0, sat = 0, val = 1; // interior color = white

			if (k < data->max_it)
			{ // exterior and boundary color
				double _Complex de = 2 * z * log(cabs(z)) / dz;
				hue = fmod(1 + carg(de) / (2 * M_PI), 1); // ? slope of de
				sat = 0.25;
				val = tanh(cabs(de) / ratio);
			}

			// hsv to rgb conversion
			t_color c = {0};
			hsv2rgb(hue, sat, val, &c.channels.r, &c.channels.g, &c.channels.b);
			return c;
		}
		++i;
	}
	return ((t_color){0xFFFFFF});
}

static inline void
	render(
			struct s_fragment_data *data,
			const t_kernel_settings *settings,
			const int max_it
			)
{
	struct s_kernel_closure	closure;

	closure.view = data->viewport;
	closure.settings = settings;
	closure.max_it = max_it,
	viewport_fragment(data, (void *)iter, &closure);
}

const t_kernel	*mandel_arg(t_kernel_settings *settings)
{
	static const t_kernel	kernel = {
		.name = "Mandelbrot Arg",
		.render = render,
		.default_viewport = {{-1.5, 1.5, -1.0, 1.0}},
		.default_mat = {{1, 0, 0, 1}},
		.flags = 0,
		.default_color = {0xFFFFFF},
	};
	return (&kernel);
}
