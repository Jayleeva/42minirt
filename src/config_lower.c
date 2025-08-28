#include "../inc/minirt.h"

int check_sp(t_data *data, char *sp)
{
	char	**tab;

	tab = ft_split(sp, ' ');		//liberer au moment de free toute la structure
	if (!tab || !tab[3] || tab[4])
		return (0);
	data->map[data->index] = tab;
	data->index ++;
	if (!check_coord(data, &(data->sp[data->i_sp].coord), 1))
		return (0);
	if (!check_diameter_or_height(data, &(data->sp[data->i_sp].diameter), 2))
		return (0);
	if (!check_colors(data, &(data->sp[data->i_sp].colors), 3))
		return (0);
	data->i_sp ++;
	return (1);
}

int check_pl(t_data *data, char *pl)
{
	char	**tab;

	tab = ft_split(pl, ' ');		//liberer au moment de free toute la structure
	if (!tab || !tab[3] || tab[4])
		return (0);
	data->map[data->index] = tab;
	data->index ++;
	if (!check_coord(data, &(data->pl[data->i_pl].coord), 1))
		return (0);
	if (!check_ornt(data, &(data->pl[data->i_pl].ornt), 2))
		return (0);
	if (!check_colors(data, &(data->pl[data->i_pl].colors), 2))
		return (0);
    data->i_pl ++;
	return (1);
}

int check_cy(t_data *data, char *cy)
{
	char	**tab;

	tab = ft_split(cy, ' ');		//liberer au moment de free toute la structure
	if (!tab || !tab[5] || tab[6])
		return (0);
	data->map[data->index] = tab;
	data->index ++;
	if (!check_coord(data, &(data->cy[data->i_cy].coord), 1))
		return (0);
	if (!check_ornt(data, &(data->cy[data->i_cy].ornt), 2))
		return (0);
	if (!check_diameter_or_height(data, &(data->cy[data->i_cy].diameter), 3))
		return (0);
	if (!check_diameter_or_height(data, &(data->cy[data->i_cy].height), 4))
		return (0);
	if (!check_colors(data, &(data->cy[data->i_cy].colors), 5))
		return (0);
	data->i_cy ++;
	return (1);
}