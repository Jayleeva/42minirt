#include "../inc/minirt.h"

int	hit_plane(const t_ray *r, const t_pl *pl, float tmin, float tmax, t_hit *out)
{
    t_ray       neg;
    t_vector	neg_oc;
    float       t;
    t_vector    tmp;

    // mettre coord de Origine en negatif pour la suite
    neg.o.x = r->o.x * -1;
    neg.o.y = r->o.y * -1;
    neg.o.z = r->o.z * -1;
    neg_oc = v_from_points(pl->coord, neg.o);

    if (v_dot(r->d, pl->ornt) == 0)
        return (0); // impossible de diviser par 0, donc on s'arrete la
    //t = dot product de -X (- Origine - Centre) et V divise par dot product de Direction et V
    t = v_dot(neg_oc, pl->ornt) / v_dot(r->d, pl->ornt); // si different de 0, on calcule le t.

    // verifier si t est dans les bornes, s'il n'y est pas, ne sera pas affiche
    if (t < tmin || t > tmax)
        return (0); // n'est pas dans les bornes

    // precalculer un tmp pour le v_dot
    tmp.o_x = (r->o.x + r->d.o_x * t) - pl->coord.x;
    tmp.o_y = (r->o.y + r->d.o_y * t) - pl->coord.y;
    tmp.o_z = (r->o.z + r->d.o_z * t) - pl->coord.z;

    // if dot product de (P-C, ou (O + t*D) - C) et V == 0, intersection
    if (v_dot(tmp, pl->ornt) != 0)
        return (0); // pas d'intersection

    out->t = t;
    out->p = p_add_v(r->o, v_scale(r->d, t)); // point d’impact : origine + t*direction
	out->n = v_norm(v_from_points(pl->coord, out->p)); // normale = (P - centre)/|...|
	if (v_dot(out->n, r->d) > 0.0f) // si normale inversee, reinverser
		out->n = v_scale(out->n, -1.0f);
    out->kind = PLANE;
    return (1);
}