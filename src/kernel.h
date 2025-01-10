#ifndef KERNEL_H
#define KERNEL_H

#include "draw_buffer.h"
#include "viewport.h"

struct s_kernel
{
	const char	*name;
	void		(*render)(const struct s_viewport* view, struct s_image *img);
};

extern struct s_kernel	mandel_ext_de;


#endif // KERNEL_H
