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

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '\n')
		{
			data->map[i] = ft_strdup(line);
			/*if (!data->map[i])
				return (free(line), 0);*/
			data->used[i] = line[0];
			if (!check_config(data, line))
			{
				free(line);
				line = NULL;
				return (0);
			}
			i ++;
		}
		free(line);
	}
	return (1);
}

int	first_open(t_data *data, char *s)
{
	int	fd;

	fd = open(s, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nFile invalid.\n");
		return (-1);
	}
	data->nelem = count_elem(data, fd);
	close(fd);
	if (!data->nelem)
		return (0);
	data->map = malloc((data->nelem + 1) * sizeof(char **));
	if (!data->map)
		return (0);
	data->map[data->nelem] = NULL;
	//init_map(data);
	data->used = malloc((data->nelem + 1) * sizeof(char));
	if (!data->used)
		return (0);
	return (data->nelem);
}


int	second_open(t_data *data, char *s)
{
	int	fd;

	fd = open(s, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nFile could not open.\n");
		return (0);
	}
	if (!is_map_valid(data, fd))
	{
		perror("Error\nMap invalid.\n");
		return (close(fd), 0);
	}
	close(fd);
	return (1);
}

int	is_valid(t_data *data, char *s)
{
	int	nelem;
	int	config;

	if (!is_format_valid(s, ".rt"))
	{
		perror("Error\nFile format invalid.\n");
		return (0);
	}
	printf("format : OK\n");
	nelem = first_open(data, s);
	if (!nelem)
	{
		perror("Error\nNumber of elements invalid.\n");
		return (0);
	}
	else if (nelem == -1)
		return (0);
	printf("nelem : OK\n");
	config = second_open(data, s);
	if (!config)
		return (0);
	printf("MAP IS VALID\n");
	return (1);
}
