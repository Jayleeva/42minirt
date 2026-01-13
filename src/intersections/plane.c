/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:56:42 by cyglardo          #+#    #+#             */
/*   Updated: 2025/09/30 14:42:44 by cyglardo         ###   ########.fr       */
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
