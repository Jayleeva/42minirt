/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_format_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 09:43:08 by cyglardo          #+#    #+#             */
/*   Updated: 2025/08/28 14:55:51 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_format_valid(char *file, char *extension)
{
	int	i;
	int	j;

	i = ft_strlen(file);
	j = ft_strlen(extension);
	if (!i || !j || i <= j)
		return (0);
	while (j >= 0)
	{
		if (file[i] != extension[j])
			return (0);
		i --;
		j --;
	}
	while (i)
	{
		if (file[i] == '.')
			return (0);
		i --;
	}
	return (1);
}
