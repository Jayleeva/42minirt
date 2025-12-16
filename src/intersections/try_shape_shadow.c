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
		if (index != i || kind != PLANE)
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
		if (index != i || kind != SPHERE)
		{
			if (hit_sphere(r, &d->sp[i], tmin, best->t, &tmp))
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
		if (index != i || kind != CYLINDER)
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
	any = 0;
	if (try_spheres_shadow(d, r, tmin, h))
		any = 1;
	if (try_cylinders_shadow(d, r, tmin, h))
		any = 1;
	if (try_planes_shadow(d, r, tmin, h))
		any = 1;
	return (any);
}
