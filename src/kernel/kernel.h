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
			const t_viewport* view,
			const t_kernel_settings *settings,
			t_img *img);
	/**
	 * @brief Default viewport
	 */
	const t_mat2d			default_viewport;
	/**
	 * @brief Default transformation matrix
	 */
	const t_mat2d			default_mat;
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
	 * @brief Rendering buffer
	 */
	t_img					*img;
}	t_closure;

/**
 * @brief Initializes a kernel by id
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
			t_pos size,
			t_viewport *viewport,
			t_kernel_settings *settings);

#endif // KERNEL_H
