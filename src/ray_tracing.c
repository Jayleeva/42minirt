#include "../inc/minirt.h"

void	cast_ray(t_data *data, int i, int x, int y)
{
	t_ray r;
	t_hit h;

	r = make_primary_ray(data, x, y);
	if (world_hit(data, &r, EPS, 1e30f, &h))
	{
		if (h.kind == SPHERE)
		{
			data->canvas[i].colors = data->sp[h.idx].colors;
		}
	}
	else
	{
		data->canvas[i].colors.r = 20;
		data->canvas[i].colors.g = 20;
		data->canvas[i].colors.b = 25;
	}
	data->canvas[i].x = x;
	data->canvas[i].y = y;
	data->canvas[i].color = rgb_to_hex(data->canvas[i]);
}

void ft_put_pixel(t_img_data *data, int x, int y, int color)
{
    char *pxl;

    if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
    {
        pxl = data->address + (y * data->size_line + x * (data->bits_per_pixel / 8));
        *(unsigned int *)pxl = color;
    }
}

int ray_tracing(t_data *data)
{
	int		x;
	int		y;
	int		i;

	data->img_data.endian = 1;
	data->img_data.size_line = W_WIDTH;
	data->img_data.bits_per_pixel = 1;

	data->canvas = malloc((W_HEIGHT * W_WIDTH + 1) * sizeof(t_pixel));
	if (!data->canvas)
		return (0);
	data->img_data.img_ptr = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
	data->img_data.address = mlx_get_data_addr(data->img_data.img_ptr, &(data->img_data).bits_per_pixel, &(data->img_data).size_line, &(data->img_data).endian);
	cam_prepare_view(data);
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
			ft_put_pixel(&(data->img_data), x, y, data->canvas[i].color);
			i ++;
			y ++;
		}
		x ++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_data.img_ptr, 0, 0);
	return (1);
}
