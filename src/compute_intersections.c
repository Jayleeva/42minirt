#include "../inc/minirt.h"

/*void	compute_sphere(?, t_sp sp)
{
	float	radius;
	//float	tmp;

	radius = sp.diameter / 2;
	/*tmp = radius * radius * radius;
	tmp = tmp * M_PI;
	tmp = tmp * (4/3);

	.x? * radius ++; // stocker le point dans quoi?
	.y? * radius ++;
	.z? * radius ++;
}

int compute_intersections(t_data *data)
{
	int	obj;

	obj = data->nelem - 3;
	

	/*int	i;

	i = 0;
	while (data->sp[i])
	{
		compute_sphere(data->volume, data->sp[i]);
		i ++;
	}
	i = 0;
	while (data->pl[i])
	{
		compute_plane(data->volume, data->pl[i]);
		i ++;
	}
	i = 0;
	while (data->cy[i])
	{
		compute_cylinder(data->volume, data->cy[i]);
		i ++;
	}
	return (1);
}*/



/*void	swap_lines(char **map, int i, char *str)
{
	int		j;
	char	*tmp;

	j = 0;
	while (map[j])
	{
		if (!ft_strncmp(map[j], str, ft_strlen(str)))
			tmp = map[j];
			map[j] = map[i];
			map[i] = tmp;
		i ++;
	}
}


int	is_sorted_lel(t_data *data)
{
	int	i;

	i = 3;
	while (data->map[i + 1])
	{
		if (get_z(data->map[i]) > get_z(data->map[i + 1]))
			return (0);
		i ++;
	}
	return (1);
}

int	sort_lel(t_data *data)
{
	int	i;

	i = 3;
	while (data->map[i + 1])
	{
		if (get_z(data->map[i]) > get_z(data->map[i + 1]))
			swap_lines(data->map, i, data->map[i + 1]);
		i ++;
	}
}

void	sort_map(t_data *data)
{
	if (ft_strncmp(data->map[0], "A ", 2))
		swap_lines(data->map, 0, "A ");
	if (ft_strncmp(data->map[1], "C ", 2))
		swap_lines(data->map, 1, "C ");
	if (ft_strncmp(data->map[2], "L ", 2))
		swap_lines(data->map, 2, "L ");
	while (!is_sorted_lel(data))
		sort_lel(data);
}*/

