#include "../inc/minirt.h"

static int	try_planes_shadow(t_data *d, const t_ray *r, float tmin, t_hit *best)
{
	t_hit	tmp;
	int		found;
	int		i;
	int		index;

	index = best->idx;
	int kind = best->kind;
	found = 0;
	i = 0;
	while (i < d->n_lel[1])
	{
		tmp = *best;
		if (index != i || kind != PLANE) // protection pour qu'il ne se cherche pas lui-meme 
		{		
			if (hit_plane(r, &d->pl[i], tmin, best->t, &tmp))
			{
				found = 1;
				*best = tmp;
				best->idx = i;
			}
		}
		i++;
	}
	return (found);
}
static int	try_spheres_shadow(t_data *d, const t_ray *r, float tmin, t_hit *best)
{
	t_hit	tmp;
	int		found;
	int		i;
	int		index;
	int kind = best->kind;

	index = best->idx;
	found = 0;
	i = 0;
	while (i < d->n_lel[0])
	{
		if (index != i || kind != SPHERE) // protection pour qu'il ne se cherche pas lui-meme 
		{
			// On teste si le rayon touche la sphère i
			if (hit_sphere(r, &d->sp[i], tmin, best->t, &tmp))
			{
				// Si oui -> mise à jour du "meilleur" hit (le plus proche)
				found = 1;
				*best = tmp;
				best->idx = i;
			}
		}
		i++;
	}
	return (found);
}

static int	try_cylinders_shadow(t_data *d, const t_ray *r, float tmin, t_hit *best)
{
  	t_hit	tmp;
	int		found;
	int		i;
	int		index;
	int kind = best->kind;

	index = best->idx;
	found = 0;
	i = 0;
  	while (i < d->n_lel[2])
	{
		tmp = *best;
		if (index != i || kind != CYLINDER) // protection pour qu'il ne se cherche pas lui-meme NOPE enleve l'ombre du cylindre
		{
			if (hit_cylinder(r, &d->cy[i], tmin, &tmp))
			{
				*best = tmp;
				best->idx = i;
				found = 1;
			}
		}
		i++;
	}
	return (found);
}

int	world_hit_shadow(t_data *d, const t_ray *r, float tmin, float tmax, t_hit *h)
{
	int	any;

	h->t = tmax;
	//h->idx = -1;
	//h->kind = -1;
	any = 0;
	if (try_spheres_shadow(d, r, tmin, h))
		any = 1;
	if (try_cylinders_shadow(d, r, tmin, h))
		any = 1;
	if (try_planes_shadow(d, r, tmin, h))
		any = 1;
	return (any);
}
