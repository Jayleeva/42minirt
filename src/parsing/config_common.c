#include "../inc/minirt.h"

int	not_valid(float x, float y, float z)
{
	if ((x < -1.0 || x > 1.0)
		|| (y < -1.0 || y > 1.0)
		|| (z < -1.0 || z > 1.0)
		|| (x == 0 && y == 0 && z == 0))
		return (1);
	return (0);
}

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
	if (is_empty(clr_tab, 2))
		return (free_tab(clr_tab), 0);
	if (!ft_isnum(clr_tab[0], 0)
		|| !ft_isnum(clr_tab[1], 0)
		|| !ft_isnum(clr_tab[2], 0))
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
int	check_coord(t_vector *coord, char *s)
{
	char	**coord_tab;

	coord_tab = ft_split(s, ',');
	if (!coord_tab)
		return (0);
	if (!coord_tab[2] || coord_tab[3])
		return (free_tab(coord_tab), 0);
	if (is_empty(coord_tab, 2))
		return (free_tab(coord_tab), 0);
	if (!ft_isnum(coord_tab[0], 1)
		|| !ft_isnum(coord_tab[1], 1)
		|| !ft_isnum(coord_tab[2], 1))
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
	float	x;
	float	y;
	float	z;

	ornt_tab = ft_split(s, ',');
	if (!ornt_tab)
		return (0);
	if (!ornt_tab[2] || ornt_tab[3])
		return (free_tab(ornt_tab), 0);
	if (is_empty(ornt_tab, 2))
		return (free_tab(ornt_tab), 0);
	if (!ft_isnum(ornt_tab[0], 1)
		|| !ft_isnum(ornt_tab[1], 1) || !ft_isnum(ornt_tab[2], 1))
		return (free_tab(ornt_tab), 0);
	x = _atof(ornt_tab[0]);
	y = _atof(ornt_tab[1]);
	z = _atof(ornt_tab[2]);
	if (not_valid(x, y, z))
		return (free_tab(ornt_tab), 0);
	ornt->x = x;
	ornt->y = y;
	ornt->z = z;
	free_tab(ornt_tab);
	return (1);
}

// Verifie si le ratio est valable.
int	check_ratio(float *ratio_, char *s)
{
	float	ratio;

	if (!ft_isnum(s, 1))
		return (0);
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

	if (!ft_isnum(s, 1))
		return (0);
	len = _atof(s);
	if (len < 0)
		return (0);
	*len_ = len;
	return (1);
}
