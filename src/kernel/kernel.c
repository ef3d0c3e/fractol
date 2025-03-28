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

/**
 * @file Kernel initialization
 */

#include <kernel/kernel.h>
#include <app/viewport/viewport_linear.h>

const t_kernel	*mandel_de(t_kernel_settings *settings);
const t_kernel	*mandel_exp(t_kernel_settings *settings);
const t_kernel	*mandel_arg(t_kernel_settings *settings);
const t_kernel	*mandel_smooth_it(t_kernel_settings *settings);
const t_kernel	*mandel_landing_arg(t_kernel_settings *settings);
const t_kernel	*mandel_electric(t_kernel_settings *settings);
const t_kernel	*mandel_exp_galaxy(t_kernel_settings *settings);
const t_kernel	*mandel_orbit(t_kernel_settings *settings);
const t_kernel	*mandel_tia(t_kernel_settings *settings);
const t_kernel	*burning_ship_exp(t_kernel_settings *settings);
const t_kernel	*burning_ship_de(t_kernel_settings *settings);
const t_kernel	*julia_exp(t_kernel_settings *settings);
const t_kernel	*julia_arg(t_kernel_settings *settings);
const t_kernel	*julia_exp_galaxy(t_kernel_settings *settings);
const t_kernel	*julia_de(t_kernel_settings *settings);
const t_kernel	*fatou(t_kernel_settings *settings);
const t_kernel	*ui_debug(t_kernel_settings *settings);

static const t_kernel	*kernel_list(size_t id, t_kernel_settings *settings)
{
	static const t_kernel *(*const	list[])(t_kernel_settings *settings) = {
		mandel_exp_galaxy,
		mandel_arg,
		mandel_exp,
		mandel_de,
		mandel_smooth_it,
		mandel_landing_arg,
		mandel_electric,
		mandel_tia,
		mandel_orbit,
		burning_ship_de,
		burning_ship_exp,
		julia_de,
		julia_arg,
		julia_exp,
		julia_exp_galaxy,
		fatou,
		ui_debug,
	};

	if (id >= sizeof(list) / sizeof(list[0]))
		return (NULL);
	return ((list[id])(settings));
}

const t_kernel
	*kernel_init(
			size_t id,
			t_viewport *viewport,
			t_kernel_settings *settings)
{
	const t_kernel					*kernel = kernel_list(id, settings);

	if (viewport->data)
		free(viewport->data);
	viewport->screen_to_space = view_linear_screen_to_space;
	viewport->space_to_screen = view_linear_space_to_screen;
	viewport->data = malloc(sizeof(struct s_viewport_linear_data));
	*((struct s_viewport_linear_data *)viewport->data)
		= view_linear_data(kernel->default_mat);
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
