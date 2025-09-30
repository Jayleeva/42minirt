/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:59:17 by cyglardo          #+#    #+#             */
/*   Updated: 2025/09/30 14:43:32 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*define_set(char *set, int base)
{
	int	i;
	int	j;

	set[0] = '-';
	set[1] = '+';
	i = 0;
	while (i < 10)
	{
		set[i + 2] = i + '0';
		i ++;
	}
	if (base > 10)
	{
		j = 0;
		while (i < base)
		{
			set[i + 2] = j + 'A';
			j ++;
			i ++;
		}
	}
	set[i + 2] = '\0';
	return (set);
}

static int	atoi_base_utils(int base, const char *str, int i)
{
	int	result;

	result = 0;
	while (str[i])
	{
		result = result * base;
		if (str[i] >= '0' && str[i] <= '9')
			result = result + (str[i] - '0');
		else if (str[i] >= 'a' && str[i] <= 'f')
			result = result + (str[i] - 'a' + 10);
		else if (str[i] >= 'A' && str[i] <= 'F')
			result = result + (str[i] - 'A' + 10);
		i ++;
	}
	return (result);
}

int	ft_atoi_base(const char *str, int base)
{
	int		i;
	int		n;
	int		result;
	char	*set;

	set = malloc((base + 2 + 1) * sizeof(char));
	if (!set)
		return (0);
	i = 0;
	n = 1;
	while ((str[i] >= 9 && str[i] <= 13)
		|| str[i] == ' ')
		i ++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (!is_in_set(define_set(set, base), str[i +1]))
			return (free(set), 0);
		if (str[i] == '-')
			n = n * -1;
		i ++;
	}
	free(set);
	result = atoi_base_utils(base, str, i);
	return (result * n);
}
