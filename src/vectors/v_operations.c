/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:33:08 by cyglardo          #+#    #+#             */
/*   Updated: 2025/08/28 17:44:27 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minirt.h"

// Addition de deux vecteurs
t_vector	v_add(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

// Soustraction de deux vecteurs (a - b)
t_vector	v_sub(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

// Multiplie un vecteur par un scalaire
t_vector	v_scale(t_vector a, float s)
{
	t_vector	res;

	res.x = a.x * s;
	res.y = a.y * s;
	res.z = a.z * s;
	return (res);
}

// Produit scalaire (dot product) : mesure projection entre 2 vecteurs
float	v_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	v_cross(t_vector a, t_vector b)
{
	t_vector	r;

	r.x = a.y * b.z - a.z * b.y;
	r.y = a.z * b.x - a.x * b.z;
	r.z = a.x * b.y - a.y * b.x;
	return (r);
}
