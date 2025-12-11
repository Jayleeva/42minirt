/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:16:25 by cyglardo          #+#    #+#             */
/*   Updated: 2025/09/11 13:02:16 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcpy(char *dest, char *src, int start, int end)
{
	int	i;

	i = start;
	while (i <= end)
	{
		*dest = src[i];
		dest++;
		i++;
	}
	*dest = '\0';
}
