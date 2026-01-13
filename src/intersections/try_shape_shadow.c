/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_shape_shadow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:56:42 by cyglardo          #+#    #+#             */
/*   Updated: 2026/01/13 17:00:28 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

static int	try_planes_shadow(t_data *d, const t_ray *r, t_hit *best)
{
	t_hit	tmp;
	int		found;
	int		i;
	t_hit	h;

	h.idx = best->idx;
	h.kind = best->kind;
	found = 0;
	i = 0;
	while (i < d->n_lel[1])
	{
		tmp = *best;
		if (h.idx != i || h.kind != PLANE)
		{
			if (hit_plane(r, &d->pl[i], best->t, &tmp))
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

static int	try_spheres_shadow(t_data *d, const t_ray *r, t_hit *best)
{
	t_hit	tmp;
	int		found;
	int		i;
	t_hit	h;

	h.idx = best->idx;
	h.kind = best->kind;
	found = 0;
	i = 0;
	while (i < d->n_lel[0])
	{
		if (h.idx != i || h.kind != SPHERE)
		{
			if (hit_sphere(r, &d->sp[i], best->t, &tmp))
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

static int	try_cylinders_shadow(t_data *d, const t_ray *r, t_hit *best)
{
	t_hit	tmp;
	int		found;
	int		i;
	t_hit	h;

	h.idx = best->idx;
	h.kind = best->kind;
	found = 0;
	i = 0;
	while (i < d->n_lel[2])
	{
		tmp = *best;
		if (h.idx != i || h.kind != CYLINDER)
		{
			if (hit_cylinder(r, &d->cy[i], &tmp))
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

int	world_hit_shadow(t_data *d, const t_ray *r, float tmax, t_hit *h)
{
	int	any;

	h->t = tmax;
	any = 0;
	if (try_spheres_shadow(d, r, h))
		any = 1;
	if (try_cylinders_shadow(d, r, h))
		any = 1;
	if (try_planes_shadow(d, r, h))
		any = 1;
	return (any);
}
