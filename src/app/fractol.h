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
	// mlx data
	t_xvar				*mlx;
	t_win_list			*window;

	// ui
	t_ui				ui;

	// Rendering data
	t_viewport			view;
	t_viewport			next_view;
	bool				has_next_view;
	/**
	 * @brief Current selected kernel
	 */
	const t_kernel		*kernel;
	t_kernel_settings	kernel_settings;
	int					kernel_id;
	int					max_iter;
	bool				post_pass;
	// Widgets
	int					kernel_count;
	int					selector_id;
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
	 * @brief Post processing buffer suitably aligned to hold least
	 * WIDTH*HEIGHT*16 bytes
	 */
	void				*filter_buffer;
}	t_fractol;

void
fractol_start(t_pos win_size);

// Render the selector widget
void
fractol_selector(t_fractol *f);

// Rendering ui
void
fractol_render(t_fractol *f);

void
fractol_bar(t_fractol *f);

// Renders zparam and handles mouse movement
void
fractol_zparam(t_fractol *f);

// Move ui
void
fractol_move(t_fractol *f);

#endif // FRACTOL_H
