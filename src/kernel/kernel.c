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
#include "kernel.h"
#include "app/viewport/viewport.h"
#include "app/viewport/viewport_linear.h"
#include "kernel/gradient.h"

const t_kernel	*mandel_de(t_kernel_settings *settings);
const t_kernel	*mandel_exp(t_kernel_settings *settings);
const t_kernel	*mandel_smooth_it(t_kernel_settings *settings);

static const t_kernel	*kernel_list(size_t id, t_kernel_settings *settings)
{
	static t_kernel const* (*list[])(t_kernel_settings *settings) = {
		mandel_de,
		mandel_exp,
		mandel_smooth_it,
	};

	if (id >= sizeof(list)/sizeof(list[0]))
		return (NULL);
	return (list[id])(settings);
}

const t_kernel
	*kernel_init(
			size_t id,
			t_pos size,
			t_viewport *viewport,
			t_kernel_settings *settings)
{
	const t_kernel					*kernel = kernel_list(id, settings);
	struct s_viewport_linear_data	*view_data;

	viewport->size = size,
	viewport->view = (t_mat2d){{
		-(double)size.x / size.y,
		(double)size.x / size.y,
		-1.0,
		1.0
	}},
	viewport->screen_to_space = view_linear_screen_to_space,
	viewport->space_to_screen = view_linear_space_to_screen,

	view_data = malloc(sizeof(struct s_viewport_linear_data));
	*view_data = view_linear_data(kernel->default_mat);
	viewport->data = view_data;

	return (kernel);
}

void
	kernel_deinit(
		const t_kernel *kernel,
		t_kernel_settings *settings
		)
{
	if (kernel->flags & USE_GRADIENT)
		gradient_free(&settings->gradient);
}

const char
	*kernel_name(size_t id)
{
	const t_kernel	*kernel = kernel_list(id, NULL);

	if (!kernel)
		return (NULL);
	return (kernel->name);
}
