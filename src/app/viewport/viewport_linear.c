#include "viewport_linear.h"
#include "util/matrix.h"
#include "util/vector.h"
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
view_linear_screen_to_space(const t_viewport *this, const t_pos pos, const t_vec2d delta)
{
	const t_vec2d	factor = { (this->view.data[1] - this->view.data[0]) / this->size.x, - (this->view.data[3] - this->view.data[2]) / this->size.y };
	t_vec2d			vec;

	vec.x = (pos.x - (this->size.x / 2.0) + delta.x) * factor.x;
    vec.y = (pos.y - (this->size.y / 2.0) + delta.y) * factor.y;
	vec = mat_mul_vec(&((struct s_viewport_linear_data *)this->data)->mat, &vec);
	vec.x += (this->view.data[0] + this->view.data[1]) / 2;
	vec.y += (this->view.data[2] + this->view.data[3]) / 2;

	return (vec);
}

t_pos
view_linear_space_to_screen(const t_viewport *this, const t_vec2d pos)
{
    const t_vec2d factor = {
        this->size.x / (this->view.data[1] - this->view.data[0]),  // X scaling factor
        -this->size.y / (this->view.data[3] - this->view.data[2])  // Y scaling factor (flipped for screen-space)
    };

    const t_mat2d *mat = &((struct s_viewport_linear_data *)this->data)->mat;
    t_vec2d vec;

    // Translate position relative to the center of the viewport (so the transformation matrix works from center)
    vec = (t_vec2d){
        pos.x - (this->view.data[0] + this->view.data[1]) / 2.0,  // X translation
        pos.y - (this->view.data[2] + this->view.data[3]) / 2.0   // Y translation
    };

    // Apply scaling first to ensure the correct aspect ratio and relative position
    vec.x = vec.x * factor.x;
    vec.y = vec.y * factor.y;

    // Now apply the transformation matrix (rotation, skewing, etc.)
    vec = mat_mul_vec(mat, &vec);

    // Translate the final result to screen space, taking into account the viewport's position
    vec.x = vec.x + (this->size.x / 2.0);  // Translate to screen space
    vec.y = vec.y + (this->size.y / 2.0);  // Translate to screen space

    return (t_pos){vec.x, vec.y};
}
