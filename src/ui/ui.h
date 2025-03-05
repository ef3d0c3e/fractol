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

# include "util/vector.h"
# include <ui/event.h>
# include <ui/draw.h>

typedef struct s_fractol	t_fractol;

/**
 * @brief Program's ui component
 */
typedef struct s_ui
{
	/**
	 * @brief UI sizes in pixels
	 */
	t_pos				size;
	// Events
	enum e_mousecode	mouse_down;
	/**
	 * @brief Mouse position during last event
	 */
	t_pos				mouse_pos;
	t_event				event;
	void				(*ui_loop)(t_fractol *f);
	/*
	 * @brief Render :ramebuffer
	 */
	t_img				*render;
	t_vec2d				img_pos;
	/**
	 * @brief UI Draw list
	 */
	t_drawqueue			ui_queue;
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
 * @brief Updates the ui
 */
void
ui_update(t_fractol *f);

#endif // UI_H
