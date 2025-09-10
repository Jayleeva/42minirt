#include "../inc/minirt.h"

int	rgb_to_hex(t_pixel pixel)
{
	int		tmp[6];
	char	s[6];
	int		ret;
	int		i;

	tmp[0] = pixel.colors.r / 16;
	tmp[1] = pixel.colors.r % 16;
	tmp[2] = pixel.colors.g / 16;
	tmp[3] = pixel.colors.g % 16;
	tmp[4] = pixel.colors.b / 16;
	tmp[5] = pixel.colors.b % 16;
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] > 9)
			s[i] = tmp[i] + 'A' + (tmp[i] - 10);
		else
			s[i] = tmp[i] + '0';
		i ++;
	}
	ret = ft_atoi_base(s, 16);
	return (ret);
}

int	cast_ray(t_data *data, int i, int x, int y)
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
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, data->canvas[i].color);
			i ++;
			y ++;
		}
		x ++;
	}

	return (1);
}
