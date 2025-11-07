/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:16:25 by cyglardo          #+#    #+#             */
/*   Updated: 2025/09/30 14:43:09 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*join_buffer(char *line, char *buffer)
{
	char	*temp;

	temp = line;
	line = ft_strjoin(temp, buffer);
	free(temp);
	return (line);
}
