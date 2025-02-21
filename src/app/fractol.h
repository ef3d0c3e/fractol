/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FRACTOL_H
# define FRACTOL_H

# include <kernel/kernel.h>
# include "viewport/viewport.h"
# include <ui/ui.h>

# include "../minilibx-linux/mlx_int.h"
# include <stdbool.h>

/**
 * @brief Program data
 */
typedef struct	s_fractol
{
	// mlx data
	t_xvar			*mlx;
	t_win_list		*window;

	// ui
	t_ui			ui;

	// Rendering data
	t_viewport		view;
	t_viewport		last_view;
	/**
	 * @brief Current selected kernel
	 */
	const t_kernel		*kernel;
	t_kernel_settings	kernel_settings;
	int					kernel_id;
}	t_fractol;

t_fractol	fractol_init();

#endif // FRACTOL_H
