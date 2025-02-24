/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef KERNEL_H
# define KERNEL_H

# include <util/math.h>
# include <ui/image.h>
# include <kernel/gradient.h>
# include <app/viewport/viewport.h>
# include <stdint.h>

typedef union u_kernel_settings
{
	t_gradient	gradient;
}	t_kernel_settings;

typedef enum e_kernel_flags
{
	USE_GRADIENT = (1L<<0),
}	t_kernel_flags;

/**
 * @brief Rendering kernel struct
 */
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
	void		(*render)(
			struct s_fragment_data *data,
			const t_kernel_settings *settings,
			const int max_it);
	/**
	 * @brief Default viewport
	 */
	const t_mat2d			default_viewport;
	/**
	 * @brief Default transformation matrix
	 */
	const t_mat2d			default_mat;

	const t_kernel_flags	flags;
}	t_kernel;

/**
 * @brief Data passed to the kernel
 */
typedef struct s_kernel_closure
{
	/**
	 * @brief Viewport
	 */
	const t_viewport		*view;
	/**
	 * @brief Kernel settings
	 */
	const t_kernel_settings	*settings;
	/**
	 * @brief Max iteration count
	 */
	int						max_it;
	/**
	 * @brief Custom data passed by the kernel
	 */
	void					*data;
}	t_closure;

/**
 * @brief Initializes a kernel by id
 *
 * This function will initialize the kernel with it's default given settings.
 * It will overwrite the given `viewport` and `settings` for the newly loaded
 * kernel. It may allocate a temporary buffer to store data for the viewport.
 * Which is the reason why `kernel_deinit` has to be called.
 *
 * @param id Id of the kernel
 * @param size Kernel raster sizes
 * @param viewport Output viewport
 * @param settings Output settings
 *
 * @returns A static address to the initialized kernel
 */
const t_kernel
	*kernel_init(
			size_t id,
			t_viewport *viewport,
			t_kernel_settings *settings);

/**
 * @brief Cleanly deinitializes the current kernel
 *
 * Must initialize another kernel before calling to `ui_update`
 *
 * @param kernel Kernel to deinitialize
 * @param settings Settings for the kernel
 */
void
kernel_deinit(
		const t_kernel *kernel,
		t_kernel_settings *settings
		);

/**
 * @brief Gets the name of a kernel
 *
 * @param id If of the kernel
 *
 * @returns The name of the kernel or NULL
 */
const char
	*kernel_name(size_t id);

#endif // KERNEL_H
