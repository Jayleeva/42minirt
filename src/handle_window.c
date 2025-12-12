#include "../inc/minirt.h"

// Libere la memoire allouee.
void	free_all(t_data *data)
{
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
	if (data->canvas)
		free(data->canvas);
}

// Detruit les images, la fenetre, et lance la liberation de toute la memoire allouee.
int	on_destroy(t_data *data)
{
	if (!data)
		return (0);
	if (data->img.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_all(data);
	exit(0);
	return (0);
}

// Gere les inputs claviers.
int	on_keypress(int keycode, t_data *data)
{
	if (keycode == K_Q || keycode == K_ESC)
		on_destroy(data);
	return (0);
}

//Initialise la fenetre, l'ouvre, lance le ray tracing, fait tourner le programme jusqu'a sa fermeture, detruit tout.
void	window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		on_destroy(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, W_WIDTH, W_HEIGHT, "Minirt");
	if (!data->win_ptr)
		on_destroy(data);
	ray_tracing(data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, data);
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy,
		data);
	mlx_loop(data->mlx_ptr);
	on_destroy(data);
}
