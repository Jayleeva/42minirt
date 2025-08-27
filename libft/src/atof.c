/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:59:17 by cyglardo          #+#    #+#             */
/*   Updated: 2024/10/23 12:33:05 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	_atof(char *str)
{
    char    **tab;
    float   result;

    tab = ft_split(str, '.');
    if (!tab || tab[2])
        return (0);
    result = ft_atoi(tab[0] + (ft_atoi(tab[1]) / 10));
    return (result);
}