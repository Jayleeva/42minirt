#include "../inc/minirt.h"

int	check_config(t_data *data, char *line)
{
	if (!ft_strncmp(line, "A ", 2))
	{
		printf("IT'S AN A\n");
		return (check_a(data, line));
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		printf("IT'S A C\n");
		return (check_c(data, line));
	}
	else if (!ft_strncmp(line, "L ", 2))
	{
		printf("IT'S A L\n");
		return (check_l(data, line));
	}
	else if (!ft_strncmp(line, "sp ", 3))
	{
		printf("IT'S A sp\n");
		return (check_sp(data, line));
	}
	else if (!ft_strncmp(line, "pl ", 3))
	{
		printf("IT'S A pl\n");
		return (check_pl(data, line));
	}
	else if (!ft_strncmp(line, "cy ", 3))
	{
		printf("IT'S A cy\n");
		return (check_cy(data, line));
	}
	else
		return (0);
	return (1);
}

int	is_map_valid(t_data *data, int fd)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	while ((line = get_next_line(fd)))
	{
		if (line[0] == '\n')
			printf("empty line\n");
		else
		{
			data->map[i] = ft_strdup(line);
			data->used[i] = line[0];
			if (!check_config(data, line))
				return (0); // free
		}
		i ++;
	}
	if (is_element_missing(data))
		return (0);
	close(fd);
	free(line);
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
	data->map = malloc((nelem + 1) * sizeof(char *));
	if (!data->map)
		return (0);
	data->map[nelem] = NULL;
	data->used = malloc((nelem + 1) * sizeof(char));
	if (!data->used)
		return (0);
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
