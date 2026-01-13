/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabatut <eihwaz.42@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:16:08 by llabatut          #+#    #+#             */
/*   Updated: 2026/01/13 17:16:12 by llabatut         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	hit_plane(const t_ray *r, const t_pl *pl, float tmax, t_hit *out)
{
	float		denom;
	float		t;
	t_vector	p;
	t_vector	n;

	n = v_norm(pl->ornt);
	denom = v_dot(r->d, n);
	if (fabsf(denom) < 1e-6f)
		return (0);
	t = v_dot(v_sub(pl->coord, r->o), n) / denom;
	if (t < EPS || t > tmax)
		return (0);
	p = v_add(r->o, v_scale(r->d, t));
	out->t = t;
	out->p = p;
	out->n = n;
	if (v_dot(out->n, r->d) > 0.0f)
		out->n = v_scale(out->n, -1.0f);
	out->kind = PLANE;
	return (1);
}
