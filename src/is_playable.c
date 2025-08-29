#include "../inc/minirt.h"

int	check_config(t_data *data, char *line)
{
	if (!ft_strncmp(line, "A ", 2))
		return (check_a(data, line));
	else if (!ft_strncmp(line, "C ", 2))
		return (check_c(data, line));
	else if (!ft_strncmp(line, "L ", 2))
		return (check_l(data, line));
	else if (!ft_strncmp(line, "sp ", 3))
		return (check_sp(data, line));
	else if (!ft_strncmp(line, "pl ", 3))
		return (check_pl(data, line));
	else if (!ft_strncmp(line, "cy ", 3))
		return (check_cy(data, line));
	else
		return (0);
	return (1);
}

int	is_map_valid(t_data *data, int fd)
{
	char	*line;
	int		i;
	int		j;
	char	*tmp;

	line = NULL;
	i = 0;
	j = 0;
	while ((line = get_next_line(fd)))
	{
		if (line[0] != '\n')
		{
			data->map[j] = ft_strdup(line);
			data->used[j] = line[0];
			tmp = line;
			if (!check_config(data, line))
				return (free(line), 0); // free
			free(tmp);
			j ++;
		}
		i ++;
	}
	if (is_element_missing(data))
		return (0);
	close(fd);

	return (1);
}

int	first_open(t_data *data, char *s)
{
	int	fd;
	int	nelem;

	fd = open(s, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nFile invalid.\n");
		return (0);
	}
	nelem = count_elem(data, fd);
	close(fd);
	printf("nelem = %d\n", nelem);
	data->map = malloc((nelem + 1) * sizeof(char *));
	if (!data->map)
		return (0);
	data->map[nelem] = NULL;
	data->used = malloc((nelem + 1) * sizeof(char));
	if (!data->used)
		return (0);
	data->used[nelem] = '\0';
	return (nelem);
}

int	is_valid(t_data *data, char *s)
{
	int	fd;
	int	nelem;

	if (!is_format_valid(s, ".rt"))
	{
		perror("Error\nFile format invalid.\n");
		return (0);
	}
	nelem = first_open(data, s);
	if (!nelem)
		return (0);
	fd = open(s, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nFile could not open.\n");
		return (0);
	}
	if (!is_map_valid(data, fd))
	{
		perror("Error\nMap invalid.\n");
		return (0);
	}
	return (1);
}
