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
typedef struct s_fractol
{
	/**
	 * @brief MLX handle
	 */
	t_xvar				*mlx;
	/**
	 * @brief MLX window handle
	 */
	t_win_list			*window;
	/**
	 * @brief UI component
	 */
	t_ui				ui;
	/**
	 * @brief Downsampling factor
	 *
	 * Set via option `-d`|`--downsample`, defaults to 1
	 */
	int					downsampling;
	/**
	 * @brief Current viewport
	 */
	t_viewport			view;
	/**
	 * @brief Next viewport (set to becomne current viewport after
	 * fractol_render is called)
	 */
	t_viewport			next_view;
	/**
	 * @brief Whether the `next_view` viewport is valid
	 */
	bool				has_next_view;
	/**
	 * @brief Current selected kernel
	 */
	const t_kernel		*kernel;
	/**
	 * @brief Setting for the current kernel
	 */
	t_kernel_settings	kernel_settings;
	/**
	 * @brief ID of the current kernel
	 */
	int					kernel_id;
	/**
	 * @brief Max iteration count
	 */
	int					max_iter;
	/**
	 * @brief Whether a render post-pass is selected.
	 *
	 * Post pass will only re-sample pixels with the kernel's `default_color`
	 */
	bool				post_pass;
	/**
	 * @brief Number of available kernels
	 */
	int					kernel_count;
	/**
	 * @brief Position of the selector widget
	 */
	t_pos				selector_pos;
	/**
	 * @brief Whether the selector is shown
	 */
	bool				selector_shown;
	/**
	 * @brief Set to true when in need fo re-rendering next frame
	 */
	bool				needs_render;
	/**
	 * @brief Set to true when in need or supersampling
	 */
	bool				needs_resample;
	/**
	 * @brief Whether resample debugging is requested
	 *
	 * This will render a grayscale image iundicating the resampling weights
	 * computed for the current image.
	 */
	bool				needs_resample_debug;
	/**
	 * @brief Whether gradient debugging is requested
	 *
	 * This will render the gradient at the bottom of the window.
	 */
	bool				needs_gradient_debug;
	/**
	 * @brief Post processing buffer suitably aligned to hold least
	 * WIDTH*HEIGHT*16 bytes
	 */
	void				*filter_buffer;
}	t_fractol;

/**
 * @brief Start the program
 *
 * Parameters are the ones parsed from command line
 *
 * @param win_size Window size
 * @param downsampling downsampling factor
 * @param kernel Initial kernel id
 */
void
fractol_start(t_pos win_size, int downsampling, int kernel);

/**
 * @brief Displays the selector widget
 *
 * @param f Fractol instance
 */
void
fractol_selector(t_fractol *f);

/**
 * @brief Renders to raster if requested
 *
 * @param f Fractol instance
 */
void
fractol_render(t_fractol *f);

/**
 * @brief Handles misc ui (iteration count and misc buttons)
 *
 * @param f Fractol instance
 */
void
fractol_ui(t_fractol *f);

/**
 * @brief Handles secondary parameter selection (using right click)
 *
 * @param f Fractol instance
 */
void
fractol_zparam(t_fractol *f);

/**
 * @brief Handles zooming and panning the window to move the raster
 *
 * @param f Fractol instance
 */
void
fractol_move(t_fractol *f);

/**
 * @brief Directly saves a screenshot
 *
 * @param f Fractol instance
 */
void
fractol_screenshot(t_fractol *f);

#endif // FRACTOL_H
