#include "../inc/minirt.h"

int ray_tracing(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < W_WIDTH)
	{
		y = 0;
		while (y < W_HEIGHT)
		{
			(void)data;
			//cast_ray(x, y);
			//compute_intersections(data, x, y);
			//set_color(data, x, y);
			//mlx_pixel_put(xvar, win, x, y, color);
			y ++;
		}
		x ++;
	}
	return (1);
}