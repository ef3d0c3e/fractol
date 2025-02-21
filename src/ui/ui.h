/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef UI_H
# define UI_H

/**
 * @file Fractol's ui manager
 */

# include <ui/draw.h>
# include <util/pos.h>
# include <stdbool.h>

typedef struct s_fractol	t_fractol;

/**
 * @brief Program's ui component
 */
typedef struct s_ui
{
	/**
	 * @brief UI sizes in pixels
	 */
	t_pos		size;
	// Events
	bool		mouse_down;
	t_pos		mouse_pos;
	t_pos		mouse_delta;
	t_pos		img_pos;
	// Selector widget
	size_t		kernel_count;
	int			selector_id;
	bool		selector_shown;
	/**
	 * @brief Set to true when in need fo re-rendering next frame
	 */
	bool		needs_render;
	/**
	 * @brief Set to true when in need or supersampling
	 */
	bool		needs_resample;
	/*
	 * @brief Render :ramebuffer
	 */
	t_img		*render;
	/**
	 * @brief Post processing buffer suitably aligned to hold least
	 * WIDTH*HEIGHT*16 bytes
	 */
	void		*filter_buffer;
	/**
	 * @brief UI Draw list
	 */
	t_drawqueue	ui_queue;
}	t_ui;

/**
 * @brief Initializes ui
 */
t_ui
ui_init(t_fractol *f, const t_pos size);
/**
 * @brief Deinitializes ui
 */
void
ui_deinit(t_fractol *f, t_ui *ui);
/**
 * @brief Draws the ui
 */
int
ui_draw(t_fractol *f);

#endif // UI_H
