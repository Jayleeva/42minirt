#include "../inc/minirt.h"

// Remplis la map de NULL pour initialiser les valeurs.
int	fill_map(t_data *data, int i)
{
	while (i < data->nelem)
	{
		data->map[i] = NULL;
		i ++;
	}
	data->map[i] = NULL;
	return (1);
}

// Initialise les elements en majuscules.
static void	init_uppercases(t_data *data)
{
	data->a.ratio = -1.0;
	data->a.colors.r = -1;
	data->a.colors.g = -1;
	data->a.colors.b = -1;
	data->c.coord.x = 0.0;
	data->c.coord.y = 0.0;
	data->c.coord.z = 0.0;
	data->c.ornt.x = 0.0;
	data->c.ornt.y = 0.0;
	data->c.ornt.z = 0.0;
	data->c.fov = -1;
	data->l.coord.x = 0.0;
	data->l.coord.y = 0.0;
	data->l.coord.z = 0.0;
	data->l.ratio = -1.0;
}

// Initialise les donnees a NULL.
void	init(t_data *data)
{
	int	i;

	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->used = NULL;
	data->nelem = 0;
	init_uppercases(data);
	i = 0;
	while (i < 3)
	{
		data->n_lel[i] = 0;
		data->n_uel[i] = 0;
		i ++;
	}
	data->i_sp = 0;
	data->i_pl = 0;
	data->i_cy = 0;
	data->sp = NULL;
	data->pl = NULL;
	data->cy = NULL;
	data->img.img_ptr = NULL;
	data->canvas = NULL;
	data->spec.ks = 1.0f;
	data->spec.shiny = 64.0f;
}

int	main(int argc, char **argv)
{
	t_data	data;

	init(&data);
	if (argc != 2)
		return (1);
	if (!is_valid(&data, argv[1]))
	{
		on_destroy(&data);
		return (1);
	}
	print_tab(data.map);
	window(&data);
	return (0);
}
