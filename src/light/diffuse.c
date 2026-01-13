/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:56:42 by cyglardo          #+#    #+#             */
/*   Updated: 2025/09/30 14:42:44 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

/*
diffuse = max(dot(N, L), 0) * light_ratio
N = normale, L = direction vers la lumière.
*/
float	compute_diffuse(t_data *d, t_hit *h, t_vector n)
{
	t_vector	l;
	float		diff;

	l = v_norm(v_sub(d->l.coord, h->p));
	diff = v_dot(n, l);
	if (diff <= 0.0f)
		diff = 0.0f;
	return (diff * d->l.ratio);
}
