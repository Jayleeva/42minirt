/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabstri.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:56:09 by cyglardo          #+#    #+#             */
/*   Updated: 2025/08/28 14:57:58 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	tabstri(char **env, char *s)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		if (env[i][j] == s[j])
		{
			while (s[j])
			{
				if (env[i][j] != s[j])
					break ;
				j ++;
			}
			if (j == (int)ft_strlen(s))
				return (i);
		}
		i ++;
	}
	return (-1);
}
