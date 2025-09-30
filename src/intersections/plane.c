#include "../inc/minirt.h"

int	hit_plane(const t_ray *r, const t_pl *pl, float tmin, float tmax, t_hit *out)
{
    t_ray       neg_o;
    t_vector	neg_oc;
    float       t;

    // tout mettre en negatif pour la suite
    neg_o.o.x = r->o.x * -1;
    neg_o.o.y = r->o.y * -1;
    neg_o.o.z = r->o.z * -1;
    neg_oc = v_from_points(pl->coord, neg_o.o);

    if (v_dot(r->d, V) == 0)
        return (0); // impossible de diviser par 0, donc on s'arrete la
    //t = dot product de -X (- Origine - Centre) et V divise par dot product de Direction et V
    t = v_dot(neg_oc, V) / v_dot(r->d, V); // si different de 0, on calcule le t.

    // verifier si t est dans les bornes, s'il n'y est pas, ne sera pas affiche
    if (t < tmin || t > tmax)
        return (0); // n'est pas dans les bornes

    // if dot product de (P-C, ou (O + t*D) - C) et V == 0, intersection
    if (v_dot((r->o + t * r->d) - C, V) != 0)
        return (0); // pas d'intersection

    out->t = t;
    out->p = p_add_v(r->o, v_scale(r->d, t)); // point d’impact : origine + t*direction
	out->n = v_norm(v_from_points(pl->coord, out->p)); // normale = (P - centre)/|...|
	if (v_dot(out->n, r->d) > 0.0f) // si normale inversee, reinverser
		out->n = v_scale(out->n, -1.0f);
    out->kind = PLANE;
    return (1);
}

 Vector dot product is denoted with "|". 
 nrm(V) is normalized V (V/sqrt(V|V))

 A ray is defined in the following way:

   P = O + D*t

where O is the ray origin and D is the ray direction. From this we create a shape-specific equation that we solve for scalar t. Obtained t is actually the distance of the hit point from the ray origin. If t is negative, the hit point lies behind the origin, and is beyond our interest (except the CSG case, in which the point may interest us unless all hit points of the shape are behind the origin).

Throughout this article I will use a substitution for the P equation:

   P - C = D*t + X

where C is a center point of a shape that we hit and X equals O-C. 

 Plane

Definition:
C is a point that lies on the plane
V is the plane normal (unit length)

To hit a plane we notice that:

	(P-C)|V = 0

This means that the P-C vector is perpendicular to the normal, which is true when the point P lies on the plane.

Solution:

	(D*t+X)|V = 0
	D|V*t = -X|V
	t = -X|V / D|V

Before the division we should check whether D|V is nonzero. We can also check if the signs of D|V and X|V are different (if not, resulting t will be negative).

Surface normal vector at point P equals to the plane normal, unless D|V is negative, in which case N=-V. 