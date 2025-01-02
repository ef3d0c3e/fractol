#include "../minilibx-linux/mlx_int.h"
#include "../minilibx-linux/mlx.h"

#include "draw_buffer.h"

int main()
{
	t_xvar			*mlx;
	//t_win_list		*window;
	struct s_image img;

	mlx = mlx_init();
	img.img = *(t_img*)mlx_new_image(mlx, 1920, 1080);
	img.data = (unsigned char*)mlx_get_data_addr(&img.img, &img.bpp, &img.len, &img.endian);
	//window = mlx_new_window(mlx, 1920, 1080, "Fractol");
	
	//asm("int $3");
}
