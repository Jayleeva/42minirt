#include "../inc/minirt.h"

int	on_destroy(t_data *data)
{
	if (!data)
		return (0);
	//destroy_images(data);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	if (data->nelem)
	{
		if (data->map)
			free_tab(data->map);
	}
	if (data->used)
		free(data->used);
	if (data->n_lel[0])
		free(data->sp);
	if (data->n_lel[1])
		free(data->pl);
	if (data->n_lel[2])
		free(data->cy);
	/*if (data->n_lel[0] || data->n_lel[1] || data->n_lel[2])
		free_tab(data->order);*/
	exit(0);
	return (0);
}

int	on_keypress(int keycode, t_data *data)
{
	if (keycode == K_Q || keycode == K_ESC)
		on_destroy(data);
	return (0);
}

void	window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		on_destroy(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, W_WIDTH, W_HEIGHT, "Minirt");
	if (!data->win_ptr)
		on_destroy(data);
	//load_images(data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, data);
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy,
		data);
	mlx_loop(data->mlx_ptr);
	on_destroy(data);
}
