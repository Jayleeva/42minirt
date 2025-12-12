#include "../inc/minirt.h"

// Addition de deux vecteurs
t_vector	v_add(t_vector a, t_vector b)
{
	t_vector	res;

	res.o_x = a.o_x + b.o_x;
	res.o_y = a.o_y + b.o_y;
	res.o_z = a.o_z + b.o_z;
	return (res);
}

// Soustraction de deux vecteurs (a - b)
t_vector	v_sub(t_vector a, t_vector b)
{
	t_vector	res;

	res.o_x = a.o_x - b.o_x;
	res.o_y = a.o_y - b.o_y;
	res.o_z = a.o_z - b.o_z;
	return (res);
}

// Multiplie un vecteur par un scalaire
t_vector	v_scale(t_vector a, float s)
{
	t_vector	res;

	res.o_x = a.o_x * s;
	res.o_y = a.o_y * s;
	res.o_z = a.o_z * s;
	return (res);
}

// Produit scalaire (dot product) : mesure projection entre 2 vecteurs
float	v_dot(t_vector a, t_vector b)
{
	return (a.o_x * b.o_x + a.o_y * b.o_y + a.o_z * b.o_z);
}

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

t_vector	v_cross(t_vector a, t_vector b)
{
	t_vector	r;

	r.o_x = a.o_y * b.o_z - a.o_z * b.o_y;
	r.o_y = a.o_z * b.o_x - a.o_x * b.o_z;
	r.o_z = a.o_x * b.o_y - a.o_y * b.o_x;
	return (r);
}

t_vector	v_minus_float(t_vector v, float f)
{
	t_vector	res;

	res.o_x = v.o_x + f;
	res.o_y = v.o_y + f;
	res.o_z = v.o_z + f;
	return (res);
}