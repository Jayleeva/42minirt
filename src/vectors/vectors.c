#include "../inc/minirt.h"

// Crée un vecteur à partir de 3 floats
t_vector	v_make(float x, float y, float z)
{
	t_vector	v;

	v.o_x = x;
	v.o_y = y;
	v.o_z = z;
	return (v);
}

// Crée un point à partir de 3 floats
t_point	p_make(float x, float y, float z)
{
	t_point	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

// Calcule le vecteur allant du point a au point b (b - a)
t_vector	v_from_points(t_point a, t_point b)
{
	t_vector	v;

	v.o_x = b.x - a.x;
	v.o_y = b.y - a.y;
	v.o_z = b.z - a.z;
	return (v);
}

// Ajoute un vecteur à un point (déplace le point)
t_point	p_add_v(t_point p, t_vector v)
{
	t_point	res;

	res.x = p.x + v.o_x;
	res.y = p.y + v.o_y;
	res.z = p.z + v.o_z;
	return (res);
}
