#include "viewport_linear.h"
#include "util/matrix.h"
#include <util/math.h>

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
view_linear_screen_to_space(const t_viewport *this, const t_pos pos)
{
	const t_mat2d	*mat = &((struct s_viewport_linear_data *)this->data)->mat;
	const t_vec2d vec = {
		(this->view.data[0] + ((double)pos.x / this->size.x)
			* (this->view.data[1] - this->view.data[0])),
		(this->view.data[2] + ((double)pos.y / this->size.y)
		 	* (this->view.data[3] - this->view.data[2]))
	};

	return (mat_mul_vec(mat, &vec));
}

t_pos
view_linear_space_to_screen(const t_viewport *this, const t_vec2d pos)
{
	const t_mat2d	*mat = &((struct s_viewport_linear_data *)this->data)->inv;
	const t_vec2d	pre = mat_mul_vec(mat, &pos);

	return ((t_pos){
		// Left offset
		(pre.x - this->view.data[0])
		 	// Normalize to [0, 1]
		 	/ (this->view.data[1] - this->view.data[0])
			// Scale to screen width
			* this->size.x,
		// Top offset
		(- pre.y - this->view.data[2])
		 	// Normalize to [0, 1]
		 	/ (this->view.data[3] - this->view.data[2])
			// Scale to screen height
			* this->size.y
	});
}
