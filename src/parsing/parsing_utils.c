#include "../inc/minirt.h"

int	is_n_uel_valid(t_data *data)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (data->n_uel[i] != 1)
			return (0);
		i ++;
	}
	return (1);
}

int	alloc_lel(t_data *data)
{
	if (data->n_lel[0] > 0)
	{
		data->sp = malloc((data->n_lel[0] + 1) * sizeof(t_sp));
		if (!data->sp)
			return (0);
	}
	if (data->n_lel[1] > 0)
	{
		data->pl = malloc((data->n_lel[1] + 1) * sizeof(t_pl));
		if (!data->pl)
			return (0);
	}
	if (data->n_lel[2] > 0)
	{
		data->cy = malloc((data->n_lel[2] + 1) * sizeof(t_sp));
		if (!data->cy)
			return (0);
	}
	return (1);
}

int	increment_elem(t_data *data, char *line)
{
	if (!ft_strncmp(line, "A ", 2))
		data->n_uel[0]++;
	else if (!ft_strncmp(line, "C ", 2))
		data->n_uel[1]++;
	else if (!ft_strncmp(line, "L ", 2))
		data->n_uel[2]++;
	else if (!ft_strncmp(line, "sp ", 3))
		data->n_lel[0]++;
	else if (!ft_strncmp(line, "pl ", 3))
		data->n_lel[1]++;
	else if (!ft_strncmp(line, "cy ", 3))
		data->n_lel[2]++;
	else
		return (0);
	return (1);
}

int	count_elem(t_data *data, int fd)
{
	char	*line;
	int		count;

	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '\n')
			count ++;
		if (!increment_elem(data, line))
			return (free(line), 0);
		free(line);
	}
	if (!is_n_uel_valid(data))
		return (0);
	if (!alloc_lel(data))
		return (0);
	return (count);
}

void	free_big_tab(char ***bigtab)
{
	(void)bigtab;
	printf("liberer memoire\n");
}
