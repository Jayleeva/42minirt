#include "../inc/minirt.h"

int check_A(t_data *data, char *A)
{
	float	ratio;
	char	**colors;
	int		R;
	int		G;
	int		B;
	char	**tab;

	tab = ft_split(A, ' ');
	if (!tab || !tab[2] || tab[3])
		return (0);
	data->map[data->index] = tab;
	data->index ++;
	ratio = ft_atof(tab[1]);
	if (ratio < 0.0 || ratio > 1.0)
		return (0);						//attention a la memoire allouee
	data->A.ratio = ratio;
	colors = ft_split(tab[2], ',');
	if (!colors || !colors[2] || colors[3])
		return (0);
	R = ft_atoi(colors[0]);
	G = ft_atoi(colors[1]);
	B = ft_atoi(colors[2]);
	if ((R < 0 || R > 255) || (G < 0 || G > 255) || (B < 0 || B > 255))
		return (0);
	data->A.colors.R = R;
	data->A.colors.G = G;
	data->A.colors.B = B;
	return (1);
}

int check_C(t_data *data, char *C)
{
	char	**coord;
	char	**ornt;
	float	o_x;
	float	o_y;
	float	o_z;
	int		fov;
	char	**tab;

	tab = ft_split(C, ' ');
	if (!tab || !tab[3] || tab[4])
		return (0);
	data->map[data->index] = tab;
	data->index ++;
	coord = ft_split(tab[1], ',');
	if (!coord || !coord[2] || coord[3])
		return (0);
	data->C.coord.x = ft_atof(coord[0]);
	data->C.coord.y = ft_atof(coord[1]);
	data->C.coord.z = ft_atof(coord[2]);

	ornt = ft_split(tab[2], ',');
	if (!ornt || !ornt[2] || ornt[3])
		return (0);
	o_x = ft_atof(ornt[0]);
	o_y = ft_atof(ornt[1]);
	o_z = ft_atof(ornt[2]);
	if ((o_x < -1.0 || o_x > 1.0) || (o_y < -1.0 || o_y > 1.0) || (o_z < -1.0 || o_z > 1.0))
		return (0);
	data->C.ornt.o_x = 0;
	data->C.ornt.o_y = 0;
	data->C.ornt.o_z = 0;
	
	fov = ft_atoi(tab[3]);
	if (fov < 0 || fov > 180)
		return (0);
	data->C.fov = fov;
	return (1);
}

int check_L(t_data *data, char *L)
{
	char	**coord;
	float	ratio;
	char	**tab;

	tab = ft_split(L, ' ');
	if (!tab || !tab[2] || tab[3])
		return (0);
	data->map[data->index] = tab;
	data->index ++;
	coord = ft_split(tab[1], ',');
	if (!coord || !coord[2] || coord[3])
		return (0);
	data->L.coord.x = ft_atof(coord[0]);
	data->L.coord.y = ft_atof(coord[1]);
	data->L.coord.z = ft_atof(coord[2]);

	ratio = ft_atof(tab[2]);
	if (ratio < 0.0 || ratio > 1.0)
		return (0);
	data->L.ratio = ratio;
	return (1);
}