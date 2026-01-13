/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_upper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabatut <eihwaz.42@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:15:02 by llabatut          #+#    #+#             */
/*   Updated: 2026/01/13 17:15:02 by llabatut         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Verifie si les configs de la lumiere ambiante sont valables.
int	check_a(t_data *data, char *type)
{
	char	**tab;
	char	*trim;

	tab = ft_split(type, ' ');
	if (!tab)
		return (0);
	if (!tab[2] || tab[3] || is_empty(tab, 2))
		return (free_tab(tab), 0);
	if (!check_ratio(&(data->a.ratio), tab[1]))
		return (free_tab(tab), 0);
	trim = ft_strtrim(tab[2], "\n");
	if (!trim)
		return (free_tab(tab), 0);
	if (!*trim)
		return (free_tab(tab), free(trim), 0);
	if (!check_colors(&(data->a.colors), trim))
		return (free_tab(tab), free(trim), 0);
	free_tab(tab);
	free(trim);
	printf("check A : OK\n");
	return (1);
}

// Verifie si les configs de la camera sont valables.
int	check_c(t_data *data, char *type)
{
	char	**tab;
	char	*trim;

	tab = ft_split(type, ' ');
	if (!tab)
		return (0);
	if (!tab[3] || tab[4] || is_empty(tab, 2))
		return (free_tab(tab), 0);
	if (!check_coord(&(data->c.coord), tab[1]))
		return (free_tab(tab), 0);
	if (!check_ornt(&(data->c.ornt), tab[2]))
		return (free_tab(tab), 0);
	trim = ft_strtrim(tab[3], "\n");
	if (!trim)
		return (free_tab(tab), 0);
	if (!*trim)
		return (free_tab(tab), free(trim), 0);
	if (!check_fov(&(data->c.fov), trim))
		return (free_tab(tab), free(trim), 0);
	free_tab(tab);
	free(trim);
	printf("check C : OK\n");
	return (1);
}

// Verifie si les configs de la source de lumiere sont valables.
int	check_l(t_data *data, char *type)
{
	char	**tab;
	char	*trim;

	tab = ft_split(type, ' ');
	if (!tab)
		return (0);
	if (!tab[2] || tab[3] || is_empty(tab, 2))
		return (free_tab(tab), 0);
	if (!check_coord(&(data->l.coord), tab[1]))
		return (free_tab(tab), 0);
	trim = ft_strtrim(tab[2], "\n");
	if (!trim)
		return (free_tab(tab), 0);
	if (!*trim)
		return (free_tab(tab), free(trim), 0);
	if (!check_ratio(&(data->l.ratio), trim))
		return (free_tab(tab), free(trim), 0);
	free_tab(tab);
	free(trim);
	printf("check L : OK\n");
	return (1);
}

// Verifie si le fov est valable.
int	check_fov(int *fov_, char *s)
{
	int	fov;

	if (!ft_isnum(s, 0))
		return (0);
	fov = ft_atoi(s);
	if (fov < 0 || fov > 180)
		return (0);
	*fov_ = fov;
	return (1);
}
