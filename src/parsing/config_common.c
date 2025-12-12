#include "../inc/minirt.h"

// Verifie si le code rgb est valable.
int	check_colors(t_rgb *colors, char *s)
{
	char	**clr_tab;
	int		r;
	int		g;
	int		b;

	clr_tab = ft_split(s, ',');
	if (!clr_tab)
		return (0);
	if (!clr_tab[2] || clr_tab[3])
		return (free_tab(clr_tab), 0);
	r = ft_atoi(clr_tab[0]);
	g = ft_atoi(clr_tab[1]);
	b = ft_atoi(clr_tab[2]);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		return (free_tab(clr_tab), 0);
	colors->r = r;
	colors->g = g;
	colors->b = b;
	free_tab(clr_tab);
	return (1);
}

// Verifie si les coordonnees sont valables.
int	check_coord(t_point *coord, char *s)
{
	char	**coord_tab;

	coord_tab = ft_split(s, ',');
	if (!coord_tab)
		return (0);
	if (!coord_tab[2] || coord_tab[3])
		return (free_tab(coord_tab), 0);
	coord->x = _atof(coord_tab[0]);
	coord->y = _atof(coord_tab[1]);
	coord->z = _atof(coord_tab[2]);
	free_tab(coord_tab);
	return (1);
}

// Verifie si les orientations sont valables.
int	check_ornt(t_vector *ornt, char *s)
{
	char	**ornt_tab;
	float	o_x;
	float	o_y;
	float	o_z;

	ornt_tab = ft_split(s, ',');
	if (!ornt_tab)
		return (0);
	if (!ornt_tab[2] || ornt_tab[3])
		return (free_tab(ornt_tab), 0);
	o_x = _atof(ornt_tab[0]);
	o_y = _atof(ornt_tab[1]);
	o_z = _atof(ornt_tab[2]);
	if ((o_x < -1.0 || o_x > 1.0)
		|| (o_y < -1.0 || o_y > 1.0)
		|| (o_z < -1.0 || o_z > 1.0))
		return (free_tab(ornt_tab), 0);
	ornt->o_x = o_x;
	ornt->o_y = o_y;
	ornt->o_z = o_z;
	free_tab(ornt_tab);
	return (1);
}

// Verifie si le ratio est valable.
int	check_ratio(float *ratio_, char *s)
{
	float	ratio;

	ratio = _atof(s);
	if (ratio < 0.0 || ratio > 1.0)
		return (0);
	*ratio_ = ratio;
	return (1);
}

// Verifie si le diametre ou la taille est valable.
int	check_diameter_or_height(float *len_, char *s)
{
	float	len;

	len = _atof(s);
	if (len < 0)
		return (0);
	*len_ = len;
	return (1);
}
