#include "../inc/minirt.h"

// Verifie si les configs de la sphere sont valables.
int	check_sp(t_data *data, char *sp)
{
	char	**tab;

	tab = ft_split(sp, ' ');
	if (!tab)
		return (0);
	if (!tab[3] || tab[4])
		return (free_tab(tab), 0);
	if (!check_coord(&(data->sp[data->i_sp].coord), tab[1]))
		return (free_tab(tab), 0);
	if (!check_diameter_or_height(&(data->sp[data->i_sp].diameter), tab[2]))
		return (free_tab(tab), 0);
	if (!check_colors(&(data->sp[data->i_sp].colors), tab[3]))
		return (free_tab(tab), 0);
	data->i_sp ++;
	free_tab(tab);
	printf("check sp : OK\n");
	return (1);
}

// Verifie si les configs du plane sont valables.
int	check_pl(t_data *data, char *pl)
{
	char	**tab;

	tab = ft_split(pl, ' ');
	if (!tab)
		return (0);
	if (!tab[3] || tab[4])
		return (free_tab(tab), 0);
	if (!check_coord(&(data->pl[data->i_pl].coord), tab[1]))
		return (free_tab(tab), 0);
	if (!check_ornt(&(data->pl[data->i_pl].ornt), tab[2]))
		return (free_tab(tab), 0);
	if (!check_colors(&(data->pl[data->i_pl].colors), tab[3]))
		return (free_tab(tab), 0);
	data->i_pl ++;
	free_tab(tab);
	printf("check pl : OK\n");
	return (1);
}

// Verifie si les configs du cylindre sont valables.
int	check_cy(t_data *data, char *cy)
{
	char	**tab;

	tab = ft_split(cy, ' ');
	if (!tab)
		return (0);
	if (!tab[5] || tab[6])
		return (free_tab(tab), 0);
	if (!check_coord(&(data->cy[data->i_cy].coord), tab[1]))
		return (free_tab(tab), 0);
	if (!check_ornt(&(data->cy[data->i_cy].ornt), tab[2]))
		return (free_tab(tab), 0);
	if (!check_diameter_or_height(&(data->cy[data->i_cy].diameter), tab[3]))
		return (free_tab(tab), 0);
	if (!check_diameter_or_height(&(data->cy[data->i_cy].height), tab[4]))
		return (free_tab(tab), 0);
	if (!check_colors(&(data->cy[data->i_cy].colors), tab[5]))
		return (free_tab(tab), 0);
	data->i_cy ++;
	free_tab(tab);
	printf("check cy : OK\n");
	return (1);
}
