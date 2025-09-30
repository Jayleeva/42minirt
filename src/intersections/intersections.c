#include "../inc/minirt.h"

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

static int	try_planes(t_data *d, const t_ray *r, float tmin, t_hit *best)
{
	t_hit	tmp;
	int		found;
	int		i;

	found = 0;
	i = 0;
	while (i < d->n_lel[1])
	{
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


int	world_hit(t_data *d, const t_ray *r, float tmin, float tmax, t_hit *h)
{
	int	any;

	h->t = tmax;
	h->idx = -1;
	h->kind = -1;
	any = 0;
	if (try_planes(d, r, tmin, h))
		any = 1;
	if (try_spheres(d, r, tmin, h))
		any = 1;
	return (any);
}
