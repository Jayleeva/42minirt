#include "../inc/minirt.h"

int check_A(t_data *data, char *A)
{
	char	**tab;

	tab = ft_split(A, ' ');		//liberer au moment de free toute la structure
	if (!tab || !tab[2] || tab[3])
		return (0);
	data->map[data->index] = tab;
	data->index ++;
	if (!check_ratio(data, &(data->A.ratio), 1))
		return (0);
	if (!check_colors(data, &(data->A.colors), 2))
		return (0);
	return (1);
}

int check_C(t_data *data, char *C)
{
	char	**tab;

	tab = ft_split(C, ' ');
	if (!tab || !tab[3] || tab[4])
		return (0);
	data->map[data->index] = tab;
	data->index ++;
	if (!check_coord(data, &(data->C.coord), 1))
		return (0);
	if (!check_ornt(data, &(data->C.ornt), 2))
		return (0);
	if (!check_fov(data, &(data->C.fov), 3))
		return (0);
	return (1);
}

int check_L(t_data *data, char *L)
{
	char	**tab;

	tab = ft_split(L, ' ');
	if (!tab || !tab[2] || tab[3])
		return (0);
	data->map[data->index] = tab;
	data->index ++;
	if (!check_coord(data, &(data->L.coord), 1))
		return (0);
	if (!check_ratio(data, &(data->L.ratio), 2))
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