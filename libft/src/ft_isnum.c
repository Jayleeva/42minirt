/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:53:46 by llabatut          #+#    #+#             */
/*   Updated: 2026/01/13 15:05:41 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_c(char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			j ++;
		i ++;
	}
	return (j);
}

int	ft_isnum(char *s, int comma)
{
	int	i;

	i = 0;
	if (!s[0])
		return (0);
	while (s[i])
	{
		if (!comma)
		{
			if (!ft_isdigit(s[i]) && s[i] != '-' && s[i] != '+')
				return (0);
		}
		else
		{
			if (!ft_isdigit(s[i]) && s[i] != '-' && s[i] != '+' && s[i] != '.')
				return (0);
			if (s[i] == '.' && (!s[i + 1] || (s[i + 1] && !ft_isdigit(s[i + 1]))))
				return (0);
			if (count_c(s, '.') > 1)
				return (0);
		}
		i ++;
	}
	return (1);
}
