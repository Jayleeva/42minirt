/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:53:46 by llabatut          #+#    #+#             */
/*   Updated: 2025/09/09 13:48:21 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	get_power(int i)
{
	int	res;

	res = 1;
	while (i)
	{
		res = res * 10;
		i --;
	}
	return (res);
}

static int	count_zeros(char *s)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (s[i] == '0')
	{
		count ++;
		i ++;
		while (s[i] == '0')
		{
			count ++;
			i ++;
		}
	}
	return (count);
}

static float	decimal_part(char *s, float result)
{
	int		zeros;
	char	*tmp;
	int		len;

	zeros = count_zeros(s);
	tmp = ft_substr(s, zeros, ft_strlen(s));
	if (!tmp)
		return (result);
	len = ft_strlen(tmp);
	if (len > 0)
	{
		if (result < 0)
			result -= (float)ft_atoi(tmp) / get_power(zeros + len);
		else
			result += (float)ft_atoi(tmp) / get_power(zeros + len);
	}
	free(tmp);
	return (result);
}

float	_atof(char *str)
{
	char	**tab;
	float	result;
	int		n;

	tab = ft_split(str, '.');
	if (!tab)
		return (0);
	n = 0;
	while (tab[n])
		n++;
	if (n > 2)
		return (free_tab(tab), 0);
	result = (float)ft_atoi(tab[0]);
	if (n == 2)
		result = decimal_part(tab[1], result);
	free_tab(tab);
	return (result);
}
