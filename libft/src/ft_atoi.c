/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:59:17 by cyglardo          #+#    #+#             */
/*   Updated: 2024/10/23 12:33:05 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	atoi_utils(const char *str, int i)
{
	int	result;

	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i ++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		n;
	int		result;
	char	*set;

	set = malloc((10 + 2 + 1) * sizeof(char));
	if (!set)
		return (0);
	i = 0;
	n = 1;
	while ((str[i] >= 9 && str[i] <= 13)
		|| str[i] == ' ')
		i ++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (!is_in_set(define_set(set, 10), str[i +1]))
			return (free(set), 0);
		if (str[i] == '-')
			n = n * -1;
		i ++;
	}
	free(set);
	result = atoi_utils(str, i);
	return (result * n);
}
