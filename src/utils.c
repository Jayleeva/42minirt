#include "../inc/minirt.h"

int count_elem(int fd)
{
	char    *line;
	int     count;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
			count ++;
		line = get_next_line(fd);
	}
	return (count);
}

int	alloc_ptr(char ***map, char *used, int nelem)
{
    map = malloc((nelem + 1) * sizeof(char **));
    if (!map)
        return (0);
    used = ft_calloc(nelem, sizeof(char));
    if (!used)
	{
        return (0);
	}
	return (1);
}

int	is_element_missing(char *used)
{
	int	i;

	i = 0;
    while (used[i])
    {
        if (used[i] == 0)
            return (1);
        i ++;
    }
	return (0);
}

int	is_usable(char *line, char *used, int i)
{
	int j;

	j = 0;
	while (used[j])
	{
		if (used[j] == line[0])
		{
			//perror("Error\n uppercase element duplicate.\n");
			return (0);
		}
		j ++;
	}
    used[i] = line[0];
	return (1);
}

void	free_big_tab(char ***bigtab)
{
	(void)bigtab;
	printf("liberer memoire\n");
}
