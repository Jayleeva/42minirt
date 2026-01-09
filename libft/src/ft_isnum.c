/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:53:46 by llabatut          #+#    #+#             */
/*   Updated: 2025/09/09 13:48:21 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnum(char *s, int comma)
{
	int	i;

	i = 0;
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
		}
		i ++;
	}
	return (1);
}
