/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel_orbit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Render the Mandelbrot set using exterior distance estimate
 */

#include "kernel/color.h"
#include <kernel/kernel.h>

#include <complex.h>

double calctrap(double _Complex c, double _Complex z, double _Complex zm, double _Complex dz)
{
	double	m;

	(void)dz;
	(void)c;
	(void)zm;
	(void)z;
	m = 1e20;
	m = fmin(fabs( creal(z) ), m);
	m = fmin(fabs( cimag(z) ), m);
	return (m);
}

static const double StripeDensity = 1.5384;

static inline t_color	iter(double _Complex c, const t_closure *data)
{
	//double _Complex	dz;
	double _Complex	z;
	//double _Complex	zm;
	//double			m;
	int				i;

	//dz = 0;
	z = 0;
	//m = 1e20;
	i = 0;

	const int skip = 6;
	double last = 0;
	double avg = 0;
	int count = 0;
	while (i < data->max_it)
	{
		//zm = z;
		//dz = 2 * z * dz + 1;
		z = z * z + c;
		//m = fmin(calctrap(c, z, zm, dz), m);
		++i;

		if (i >= skip)
		{
			last = 0.5 + 0.5 * sin(StripeDensity * atan2(cimag(z),creal(z)));
			avg += last;
			++count;
		}
		if (cabs(z)*cabs(z) >= 74468 && i>skip)
			break;
	}
	double prevAvg = (avg - last)/(count-1.0);
	avg = avg/count;
	double frac = 1 + log2(log(74468)/log(cabs(z)));
	double mix = frac * avg + (1.0 - frac) * prevAvg;
	if (i < data->max_it)
	{
		double co = mix * pow(10.0, -0.1098);
		//t_colvec cv = colvec_new(.5+.5*cos(6.2831*co),.5+.5*cos(6.2831*co + 0.4),.5+.5*cos(6.2831*co +0.7), 0.f);
		//return (colvec_to_color(&cv, 1.f));
		return (gradient_get(&data->settings->gradient, log(co)));
	}
	return ((t_color){0});
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
	closure.max_it = max_it;
	viewport_fragment(data, (t_color (*)(double _Complex, void *))iter,
		&closure);
}

const t_kernel	*mandel_orbit(t_kernel_settings *settings)
{
	static const struct s_gr_color	colors[] = {
	{{66 << 16 | 30 << 8 | 15}, 1.0},
	{{25 << 16 | 7 << 8 | 26}, 1.0}, {{9 << 16 | 1 << 8 | 47}, 1.0},
	{{4 << 16 | 4 << 8 | 73}, 1.0}, {{0 << 16 | 7 << 8 | 100}, 1.0},
	{{12 << 16 | 44 << 8 | 138}, 1.0}, {{24 << 16 | 82 << 8 | 177}, 1.0},
	{{57 << 16 | 125 << 8 | 209}, 1.0}, {{134 << 16 | 181 << 8 | 229}, 1.0},
	{{211 << 16 | 236 << 8 | 248}, 1.0}, {{241 << 16 | 233 << 8 | 191}, 1.0},
	{{248 << 16 | 201 << 8 | 95}, 1.0}, {{255 << 16 | 170 << 8 | 0}, 1.0},
	{{204 << 16 | 128 << 8 | 0}, 1.0}, {{153 << 16 | 87 << 8 | 0}, 1.0},
	{{106 << 16 | 52 << 8 | 3}, 1.0}, {{66 << 16 | 30 << 8 | 15}, 1.0}};
	static const t_kernel			kernel = {
		.name = "Mandelbrot Orbit Trap",
		.render = render,
		.default_viewport = {{-1.5, 1.5, -1.0, 1.0}},
		.default_mat = {{1, 0, 0, 1}},
		.flags = USE_GRADIENT,
		.default_color = {0x000000},
	};

	if (settings)
		settings->gradient = gradient_new(colors,
				sizeof(colors) / sizeof(colors[0]));
	return (&kernel);
}
