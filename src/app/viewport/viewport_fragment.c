/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_fragment.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "kernel/color.h"
#include "ui/image.h"
#include "util/vector.h"
#include "viewport.h"

static void	
	fragment_oversample(
		struct s_fragment_data *data,
		t_color (*shader)(t_pos pos, t_vec2d z, void *data),
		void *closure)
{
	const size_t	size = data->viewport->size.y * data->viewport->size.x;
	t_color			*shared = (t_color *)data->img->data;
	size_t			i;
	t_color			color;

#pragma omp parallel shared(shared, size) private(i, color)
	{
#pragma omp for schedule(dynamic)
		for (i = 0; i < size; ++i)
		{
			const int	oversample = data->oversampling_data[i] * 2;
			const	float factor = 1.f / (2.f * oversample + 1.f);
			const	float factor2 = factor * factor;
			const t_pos pos = (t_pos){i % data->viewport->size.x, i / data->viewport->size.x};
			float			cols[3];
			cols[0] = cols[1] = cols[2] = 0.f;
			for (int y = -oversample; y <= oversample; ++y)
			{
				for (int x = -oversample; x <= oversample; ++x)
				{
					const t_vec2d z = data->viewport->screen_to_space(data->viewport, pos, (t_vec2d){x * factor, y * factor});
					color = shader(pos, z, closure);
					cols[0] += color.channels.r / 255.f * factor2;
					cols[1] += color.channels.g / 255.f * factor2;
					cols[2] += color.channels.b / 255.f * factor2;
				}
			}
			((t_color *)shared)[i].channels.r = cols[0]  * 255.f;
			((t_color *)shared)[i].channels.g = cols[1]  * 255.f;
			((t_color *)shared)[i].channels.b = cols[2]  * 255.f;
		}
#pragma omp barrier
	}
}

void
	viewport_fragment(
		struct s_fragment_data *data,
		t_color (*shader)(t_pos pos, t_vec2d z, void *data),
		void *closure)
{
	const size_t size = data->viewport->size.y * data->viewport->size.x;
	char *shared = data->img->data;

	if (data->oversampling_data)
		return fragment_oversample(data, shader, closure);

	size_t i;
#pragma omp parallel shared(shared, size) private(i)
	{
#pragma omp for schedule(dynamic)
		for (i = 0; i < size; ++i)
		{
			const t_pos pos = (t_pos){i % data->viewport->size.x, i / data->viewport->size.x};
			const t_color color =
				shader(pos, data->viewport->screen_to_space(data->viewport, pos, (t_vec2d){0, 0}), closure);
			((t_color *)shared)[i] = color;
		}
#pragma omp barrier
	}
}
