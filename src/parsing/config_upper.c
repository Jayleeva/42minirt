#include "../inc/minirt.h"

// Verifie si les configs de la lumiere ambiante sont valables.
int	check_a(t_data *data, char *type)
{
	char	**tab;

	tab = ft_split(type, ' ');
	if (!tab)
		return (0);
	if (!tab[2] || tab[3])
		return (free_tab(tab), 0);
	if (!check_ratio(&(data->a.ratio), tab[1]))
		return (free_tab(tab), 0);
	if (!check_colors(&(data->a.colors), tab[2]))
		return (free_tab(tab), 0);
	free_tab(tab);
	printf("check A : OK\n");
	return (1);
}

// Verifie si les configs de la camera sont valables.
int	check_c(t_data *data, char *type)
{
	char	**tab;

	tab = ft_split(type, ' ');
	if (!tab)
		return (0);
	if (!tab[3] || tab[4])
		return (free_tab(tab), 0);
	if (!check_coord(&(data->c.coord), tab[1]))
		return (free_tab(tab), 0);
	if (!check_ornt(&(data->c.ornt), tab[2]))
		return (free_tab(tab), 0);
	if (!check_fov(&(data->c.fov), tab[3]))
		return (free_tab(tab), 0);
	free_tab(tab);
	printf("check C : OK\n");
	return (1);
}

// Verifie si les configs de la source de lumiere sont valables.
int	check_l(t_data *data, char *type)
{
	char	**tab;

	tab = ft_split(type, ' ');
	if (!tab)
		return (0);
	if (!tab[2] || tab[3])
		return (free_tab(tab), 0);
	if (!check_coord(&(data->l.coord), tab[1]))
		return (free_tab(tab), 0);
	if (!check_ratio(&(data->l.ratio), tab[2]))
		return (free_tab(tab), 0);
	free_tab(tab);
	printf("check L : OK\n");
	return (1);
}

// Verifie si le fov est valable.
int	check_fov(int *fov_, char *s)
{
	int	fov;

	fov = ft_atoi(s);
	if (fov < 0 || fov > 180)
		return (0);
	*fov_ = fov;
	return (1);
}
