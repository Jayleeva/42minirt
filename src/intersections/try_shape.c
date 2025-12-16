#include "../inc/minirt.h"

// Parcourt toutes les sphères de la scène et cherche la plus proche
// parmi celles que le rayon intersecte.
// Retourne 1 si au moins une sphère est touchée, 0 sinon.
static int	try_spheres(t_data *d, const t_ray *r, float tmin, t_hit *best)
{
	t_hit	tmp;
	int		found;
	int		i;

	found = 0;
	i = 0;
	while (i < d->n_lel[0])
	{	
		if (hit_sphere(r, &d->sp[i], tmin, best->t, &tmp))
		{
			found = 1;
			*best = tmp;
			best->idx = i;
		}
		i++;
	}
	return (found);
}

static int	try_cylinders(t_data *d, const t_ray *r, float tmin, t_hit *best)
{
  	t_hit	tmp;
	int		found;
	int		i;

	found = 0;
	i = 0;
  	while (i < d->n_lel[2])
	{
		tmp = *best;
		if (hit_cylinder(r, &d->cy[i], tmin, &tmp))
		{
			*best = tmp;
			best->idx = i;
			found = 1;
		}
		i++;
	}
	return (found);
}

static int	try_planes(t_data *d, const t_ray *r, float tmin, t_hit *best)
{
	t_hit	tmp;
	int		found;
	int		i;

	found = 0;
	i = 0;
	while (i < d->n_lel[1])
	{
		tmp = *best;
		if (hit_plane(r, &d->pl[i], tmin, best->t, &tmp))
		{
			found = 1;
			*best = tmp;
			best->idx = i;
		}
		i++;
	}
	return (found);
}

// Cherche l'intersection la plus proche entre le rayon 
// et tous les objets du monde.
// Initialise "h" avec les infos du hit le plus proche trouvé.
// Retourne 1 si un objet est touché, 0 sinon.
int	world_hit(t_data *d, const t_ray *r, float tmin, float tmax, t_hit *h)
{
	int	any;

	h->t = tmax;
	h->idx = -1;
	h->kind = -1;
	any = 0;
	if (try_spheres(d, r, tmin, h))
		any = 1;
	if (try_cylinders(d, r, tmin, h))
		any = 1;
	if (try_planes(d, r, tmin, h))
		any = 1;
	return (any);
}