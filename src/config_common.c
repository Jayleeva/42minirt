#include "../inc/minirt.h"

int	check_colors(t_data *data, t_rgb *colors, int i)
{
	char	**clr_tab;
	int		R;
	int		G;
	int		B;

	clr_tab = ft_split(data->map[data->index][i], ',');
	if (!clr_tab || !clr_tab[2] || clr_tab[3])
		return (0);
	R = ft_atoi(clr_tab[0]);
	G = ft_atoi(clr_tab[1]);
	B = ft_atoi(clr_tab[2]);
	if ((R < 0 || R > 255) || (G < 0 || G > 255) || (B < 0 || B > 255))
		return (free_tab(clr_tab), 0);
	colors->R = R;
	colors->G = G;
	colors->B = B;
	free_tab(clr_tab);
	return (1);
}

int	check_coord(t_data *data, t_point *coord, int i)
{
	char	**coord_tab;

	coord_tab = ft_split(data->map[data->index][i], ',');
	if (!coord_tab || !coord_tab[2] || coord_tab[3])
		return (0);
	coord->x = _atof(coord_tab[0]);
	coord->y = _atof(coord_tab[1]);
	coord->z = _atof(coord_tab[2]);
	free_tab(coord_tab);
	return (1);
}

int	check_ornt(t_data *data, t_vector *ornt, int i)
{
	char	**ornt_tab;
	float	o_x;
	float	o_y;
	float	o_z;

	ornt_tab = ft_split(data->map[data->index][i], ',');
	if (!ornt_tab || !ornt_tab[2] || ornt_tab[3])
		return (0);
	o_x = _atof(ornt_tab[0]);
	o_y = _atof(ornt_tab[1]);
	o_z = _atof(ornt_tab[2]);
	if ((o_x < -1.0 || o_x > 1.0) || (o_y < -1.0 || o_y > 1.0) || (o_z < -1.0 || o_z > 1.0))
		return (0);
	ornt->o_x = o_x;
	ornt->o_y = o_y;
	ornt->o_z = o_z;
	return (1);
}

int	check_ratio(t_data *data, float *ratio_, int i)
{
	float	ratio;

	ratio = _atof(data->map[data->index][i]);
	if (ratio < 0.0 || ratio > 1.0)
		return (0);
	*ratio_ = ratio;
	return (1);
}

int	check_fov(t_data *data, int *fov_, int i)
{
	int	fov;

	fov = ft_atoi(data->map[data->index][i]);
	if (fov < 0 || fov > 180)
		return (0);
	*fov_ = fov;
	return (1);
}