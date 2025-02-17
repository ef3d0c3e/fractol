#ifndef KERNEL_H
#define KERNEL_H

#include "draw_buffer.h"
#include "viewport.h"
#include <stdint.h>

typedef struct s_kernel
{
	/**
	 * @brief Kernel's display name
	 */
	const char	*name;
	/**
	 * @brief Initializes the kernel
	 */
	void		(*init)(const t_viewport* view);
	void		(*render)(const t_viewport* view, struct s_image *img);
}	t_kernel;

typedef struct s_kernel_closure
{
	struct s_image		*img;
	/**
	 * @brief Render buffer
	 */
	uint8_t				*buffer;
	/**
	 * @brief Viewport
	 */
	const t_viewport	*view;
}	t_closure;

uint8_t	*kernel_resize_buffer(uint8_t *buffer, t_viewport *view);

extern t_kernel	mandel_ext_de;


#endif // KERNEL_H
