#include "sfx.h"
#include "fractol.h"
#include "draw_buffer.h"
#include "../minilibx-linux/mlx.h"


t_sfx
sfx_new(const t_fractol *f, t_pos size)
{
	return ((t_sfx){
		mlx_new_image(f->mlx, size.x, size.y),
		mlx_new_image(f->mlx, size.x, size.y)
	});
}

void
sfx_free(const t_fractol *f, t_sfx *sfx)
{
	mlx_destroy_image(f->mlx, sfx->render);
	mlx_destroy_image(f->mlx, sfx->overlay);
}

void
sfx_display(const t_fractol *f, const t_sfx *sfx)
{
	
	SFX_RECT,
	SFX_LINE,
	mlx_put_image_to_window(f->mlx, f->window, sfx->overlay, 0, 0);
	ft_memcpy(sfx->overlay->data, sfx->render->data,
			sfx->render->width * sfx->render->height * sfx->render->bpp / 8);

}
