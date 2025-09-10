#include "../inc/minirt.h"

void	cast_ray(t_data *data, int i, int x, int y)
{
	data->canvas[i].x = x;
	data->canvas[i].y = y;
	data->canvas[i].colors.r = 0;
	data->canvas[i].colors.g = 255;
	data->canvas[i].colors.b = 0;
	data->canvas[i].color = rgb_to_hex(data->canvas[i]);
}

int ray_tracing(t_data *data)
{
	int	x;
	int	y;
	int	i;

	data->canvas = malloc((W_HEIGHT * W_WIDTH + 1) * sizeof(t_pixel));
	if (!data->canvas)
		return (0);
	i = 0;
	x = 0;
	while (x < W_WIDTH)
	{
		y = 0;
		while (y < W_HEIGHT)
		{
			cast_ray(data, i, x, y);
			//compute_intersections(data, x, y);
			//set_color(data, x, y);
			printf("pixel color = %X\n", data->canvas[i].color);
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, data->canvas[i].color);
			printf("hello\n");
			i ++;
			y ++;
		}
		x ++;
	}

	return (1);
}
