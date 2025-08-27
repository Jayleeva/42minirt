/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabstri.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/22/08 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/22/08 09:25:31 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int tabstri(char **env, char *s)
{
    int     i;

    i = 0;
    while (env[i])
    {
        int j = 0;
        if (env[i][j] == s[j])
        {
            while (s[j])
            {
                
                if (env[i][j] != s[j])
                    break;    
                j ++;
            }
            if (j == (int)ft_strlen(s))
                return (i);
        }
        i ++;
    }
    return (-1);
}