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
	if (data->map)
		free_tab(data->map);
	exit(0);
	return (0);
}

static void	init(t_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->map = NULL;
	//initialize_images(data);
}

void	initialize(char **tab, size_t len, int nelem)
{
	t_data	data;

    (void)tab;
	init(&data);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		on_destroy(&data);
	data.win_ptr = mlx_new_window(data.mlx_ptr, (int)len * 64,
			nelem * 64, "Minirt");
	if (!data.win_ptr)
		on_destroy(&data);
	/*load_images(&data);
	data.map = tab;
	create_map(&data);
    mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);*/
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy,
		&data);
	mlx_loop(data.mlx_ptr);
    on_destroy(&data);
}