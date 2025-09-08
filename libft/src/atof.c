/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:59:17 by cyglardo          #+#    #+#             */
/*   Updated: 2025/08/28 17:54:24 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	get_power(int i)
{
	int	res;

	res = 100;
	while (i)
	{
		res = res * 10;
		i --;
	}
	return (res);
}

static int count_zeros(char *s)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (s[i] == '0')
	{	
		count ++;
		i ++;
		while(s[i] == '0')
		{
			count ++;
			i ++;
		}
	}
	return (count);
}

float	_atof(char *str)
{
	char	**tab;
	float	result;
	int		i;
	//char	*tmp1;
	char	*tmp2;

	i = 0;
	//tmp1 = str;
	tab = ft_split(str, '.');
	//free(str);
	//free(tmp1);
	if (!tab || tab[2])
		return (0);
	result = (float)ft_atoi(tab[0]);
	if (tab[1])
	{	
		i = count_zeros(tab[1]);
		tmp2 = ft_substr(tab[1], i, ft_strlen(tab[1]));
		result = result + ((float)ft_atoi(tmp2) / get_power(i));
		free(tmp2);
	}
	free_tab(tab);
	return (result);
}
