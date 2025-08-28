/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:59:17 by cyglardo          #+#    #+#             */
/*   Updated: 2025/08/28 16:05:38 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	_atof(char *str)
{
	char	**tab;
	float	result;

	tab = ft_split(str, '.');
	printf("BAHALORS\n");
	if (!tab || tab[2])
		return (0);
	
	result = (float)ft_atoi(tab[0]);
	result = result + ((float)ft_atoi(tab[1]) / 10);
	return (result);
}
