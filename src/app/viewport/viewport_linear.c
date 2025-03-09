/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   viewport_linear.c								  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lgamba <lgamba@42.fr>					  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/18 11:54:01 by lgamba			#+#	#+#			 */
/*   Updated: 2025/02/18 17:50:12 by lgamba		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

/**
 * @brief Linear viewport implementation
 */

#include <app/viewport/viewport_linear.h>

struct s_viewport_linear_data
	view_linear_data(t_mat2d mat)
{
	t_mat2d	inv;

	inv = mat;
	mat_invert(&inv);
	return ((struct s_viewport_linear_data){
		.mat = mat,
		.inv = inv,
	});
}

t_vec2d
	view_linear_screen_to_space(
		const t_viewport *this,
		const t_vec2d pos)
{
	const t_vec2d	factor = {
		(this->view.data[1] - this->view.data[0]),
		-(this->view.data[3] - this->view.data[2])};
	t_vec2d			vec;

	vec.x = (pos.x - 0.5) * factor.x;
	vec.y = (pos.y - 0.5) * factor.y;
	vec = mat_mul_vec(&((struct s_viewport_linear_data *)this->data)->mat,
			&vec);
	vec.x += (this->view.data[0] + this->view.data[1]) / 2;
	vec.y += (this->view.data[2] + this->view.data[3]) / 2;
	return (vec);
}

t_pos
	view_linear_space_to_screen(const t_viewport *this, const t_vec2d pos)
{
	const t_vec2d	factor = {
		this->size.x / (this->view.data[1] - this->view.data[0]),
		this->size.y / (this->view.data[3] - this->view.data[2])};
	const t_mat2d	*mat = &((struct s_viewport_linear_data *)this->data)->inv;
	t_vec2d			vec;

	vec = (t_vec2d){
		pos.x - (this->view.data[0] + this->view.data[1]) / 2.0,
		pos.y - (this->view.data[2] + this->view.data[3]) / 2.0
	};
	vec.x = vec.x * factor.x;
	vec.y = vec.y * factor.y;
	vec = mat_mul_vec(mat, &vec);
	vec.x = vec.x + (this->size.x / 2.0);
	vec.y = vec.y + (this->size.y / 2.0);
	return ((t_pos){vec.x, vec.y});
}
