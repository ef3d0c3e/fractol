#ifndef KERNEL_H
#define KERNEL_H

#include "draw_buffer.h"

struct s_coor_data
{
	double	cx;
	double	cy;
	double	x;
	double	y;
	double	dx;
	double	dy;
	int		bailout;
};

struct s_kernel_options
{
	double coor_x;
	double coor_y;
	double zoom;

	double bailout;
	int max_iter;
	int anti_aliasing;
};

struct s_color_options
{
	union u_001 {
		struct s_001 {
			
		} bw;

		struct s_002 {

		} smooth_coloring;

		struct s_003 {

		} distance_estimate;

		struct s_004 {

		} strange_attractor;

		struct s_005 {

		} pickover_stalk;

		struct s_006 {

		} orbit_trap;
	} mandelbrot;
};

typedef void(*t_kernel_fn)(
		const struct s_kernel_options *kopts,
		const struct s_color_options *copts,
		struct s_draw_buffer *buf
);

struct s_kernel
{
	struct s_kernel_options	kopts;
	struct s_color_options	copts;
	t_kernel_fn				fn;
};

#endif // KERNEL_H
