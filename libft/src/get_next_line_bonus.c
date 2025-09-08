/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:16:25 by cyglardo          #+#    #+#             */
/*   Updated: 2024/11/28 17:00:03 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_strcpy(char *dest, char *src, int start, int end)
{
    int    i;

    i = 0;
    while (*src)
    {
        if (i > end)
            break;
        if (i >= start)
        {
            *dest = *src;
            dest++;
        }
        i++;
        src++;
    }
    *dest = '\0';
}

int    has_new_line(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == '\n')
            return (i + 1);
        i++;
    }
    return (0);
}

char *extract_line(char *buffer)
{
    char    *line;
    int        i;

    i = has_new_line(buffer) - 1;
    line = malloc((i + 2) * sizeof(char));
    ft_strcpy(line, buffer, 0, i);
    ft_strcpy(buffer, buffer, i + 1, ft_strlen(buffer));
    return (line);
}

char *read_line(int fd, char *buffer)
{
    int     read_bytes;
    char    *line;
    char    *temp1;
    char    *temp2;

    line = ft_strdup(buffer);
    while ((read_bytes = read(fd, buffer, BUFFER_SIZE)))
    {
        buffer[read_bytes] = '\0';
        if (has_new_line(buffer))
        {
            temp1 = line;
            temp2 = extract_line(buffer);
            line = ft_strjoin(temp1, temp2);
            free(temp1);
            free(temp2);
            return (line);
        }
        temp1 = line;
        line = ft_strjoin(temp1, buffer);
        free(temp1);
    }
    if (*buffer)
    {
        *buffer = '\0';
        return (line);
    }
    free(line);
    return (NULL);
}

char *get_next_line(int fd)
{
    static char buffer[MAX_FD][BUFFER_SIZE + 1];

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if ((has_new_line(buffer[fd])))
        return (extract_line(buffer[fd]));
    else
        return (read_line(fd, buffer[fd]));
}