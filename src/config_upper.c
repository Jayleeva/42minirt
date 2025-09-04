#include "../inc/minirt.h"

//liberer tous les split au moment de free toute la structure?
int	check_a(t_data *data, char *type)
{
	char	**tab;

	tab = ft_split(type, ' ');
	if (!tab || !tab[2] || tab[3])
		return (0);
	if (!check_ratio(&(data->a.ratio), tab[1]))
		return (0);
	if (!check_colors(&(data->a.colors), tab[2]))
		return (0);
	free_tab(tab);
	printf("check A : OK\n");
	return (1);
}

int	check_c(t_data *data, char *type)
{
	char	**tab;

	tab = ft_split(type, ' ');
	if (!tab || !tab[3] || tab[4])
		return (0);
	if (!check_coord(&(data->c.coord), tab[1]))
		return (0);
	if (!check_ornt(&(data->c.ornt), tab[2]))
		return (0);
	if (!check_fov(&(data->c.fov), tab[3]))
		return (0);
	free_tab(tab);
	printf("check C : OK\n");
	return (1);
}

int	check_l(t_data *data, char *type)
{
	char	**tab;

	tab = ft_split(type, ' ');
	if (!tab || !tab[2] || tab[3])
		return (0);
	if (!check_coord(&(data->l.coord), tab[1]))
		return (0);
	if (!check_ratio(&(data->l.ratio), tab[2]))
		return (0);
	free_tab(tab);
	printf("check L : OK\n");
	return (1);
}

int	check_fov(int *fov_, char *s)
{
	int	fov;

	fov = ft_atoi(s);
	if (fov < 0 || fov > 180)
		return (0);
	*fov_ = fov;
	return (1);
}