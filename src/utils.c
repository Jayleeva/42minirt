#include "../inc/minirt.h"

int	count_elem(t_data *data, int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
			count ++;
		if (!ft_strncmp(line, "sp ", 3))
			data->n_lel[0]++;
		else if (!ft_strncmp(line, "pl ", 3))
			data->n_lel[1]++;
		else if (!ft_strncmp(line, "cy ", 3))
			data->n_lel[2]++;
		line = get_next_line(fd);
	}
	if (!alloc_el(data))
		return (0);
	return (count);
}

int	alloc_el(t_data *data)
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

int	alloc_ptr(char ***map, char *used, int nelem)
{
	map = malloc((nelem + 1) * sizeof(char **));
	if (!map)
		return (0);
	used = ft_calloc(nelem, sizeof(char));
	if (!used)
		return (0);
	return (1);
}

int	is_element_missing(t_data *data, char *used)
{
	int	i;

	i = 0;
	while (used[i])
	{
		if (used[i] == 'A')
			data->n_uel[0]++;
		if (used[i] == 'C')
			data->n_uel[1]++;
		if (used[i] == 'L')
			data->n_uel[2]++;
		i ++;
	}
	i = 0;
	while (i < 3)
	{
		if (data->n_uel[i] != 1)
			return (1);
		i ++;
	}
	return (0);
}

void	free_big_tab(char ***bigtab)
{
	(void)bigtab;
	printf("liberer memoire\n");
}
