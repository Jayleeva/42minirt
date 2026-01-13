/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:33:08 by cyglardo          #+#    #+#             */
/*   Updated: 2025/08/28 17:44:27 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minirt.h"

int	not_valid(float x, float y, float z)
{
	if ((x < -1.0 || x > 1.0)
		|| (y < -1.0 || y > 1.0)
		|| (z < -1.0 || z > 1.0)
		|| (x == 0 && y == 0 && z == 0))
		return (1);
	return (0);
}

int	check_colors_utils(t_rgb *colors, char **clr_tab)
{
	int		r;
	int		g;
	int		b;

	r = ft_atoi(clr_tab[0]);
	g = ft_atoi(clr_tab[1]);
	b = ft_atoi(clr_tab[2]);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		return (0);
	colors->r = r;
	colors->g = g;
	colors->b = b;
	return (1);
}
