#include "../inc/minirt.h"

void	compute_sphere(t_data *data, t_sp sp)
{
	float	dot;

	dot = get_dot(sphere_point, current_pixel);
	
}

int compute_intersections(t_data *data)
{
	int	i;

	i = 0;
	while (&(data->sp[i]))
	{
		compute_sphere(data, data->sp[i]);
		i ++;
	}
	i = 0;
	while (&(data->sp[i]))
	{
		compute_plane(data, data->pl[i]);
		i ++;
	}
	i = 0;
	while (&(data->sp[i]))
	{
		compute_cylinder(data, data->cy[i]);
		i ++;
	}
	return (1);
}