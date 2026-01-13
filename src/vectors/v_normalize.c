/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_normalize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabatut <eihwaz.42@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:15:28 by llabatut          #+#    #+#             */
/*   Updated: 2026/01/13 17:15:28 by llabatut         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Carré de la longueur d'un vecteur (évite sqrt quand inutile)
float	v_len2(t_vector a)
{
	return (v_dot(a, a));
}

// Longueur d'un vecteur (norme euclidienne)
float	v_len(t_vector a)
{
	return (sqrtf(v_len2(a)));
}

// Normalise un vecteur (longueur = 1)
// Si vecteur nul -> renvoie inchangé
t_vector	v_norm(t_vector a)
{
	float		len;
	t_vector	res;

	len = v_len(a);
	if (len > 0.0f)
		res = v_scale(a, 1.0f / len);
	else
		res = a;
	return (res);
}
