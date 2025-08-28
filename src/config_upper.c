#include "../inc/minirt.h"

//liberer tous les split au moment de free toute la structure?
int	check_a(t_data *data, char *type)
{
	char	**tab;

	tab = ft_split(type, ' ');
	if (!tab || !tab[2] || tab[3])
		return (0);
	data->map[data->index] = tab;
	data->index ++;
	if (!check_ratio(data, &(data->a.ratio), 1))
		return (0);
	if (!check_colors(data, &(data->a.colors), 2))
		return (0);
	return (1);
}

int	check_c(t_data *data, char *type)
{
	char	**tab;

	tab = ft_split(type, ' ');
	if (!tab || !tab[3] || tab[4])
		return (0);
	data->map[data->index] = tab;
	data->index ++;
	if (!check_coord(data, &(data->c.coord), 1))
		return (0);
	if (!check_ornt(data, &(data->c.ornt), 2))
		return (0);
	if (!check_fov(data, &(data->c.fov), 3))
		return (0);
	return (1);
}

int	check_l(t_data *data, char *type)
{
	char	**tab;

	tab = ft_split(type, ' ');
	if (!tab || !tab[2] || tab[3])
		return (0);
	data->map[data->index] = tab;
	data->index ++;
	if (!check_coord(data, &(data->l.coord), 1))
		return (0);
	if (!check_ratio(data, &(data->l.ratio), 2))
		return (0);
	return (1);
}

int	check_fov(t_data *data, int *fov_, int i)
{
	int	fov;

	fov = ft_atoi(data->map[data->index][i]);
	if (fov < 0 || fov > 180)
		return (0);
	*fov_ = fov;
	return (1);
}
