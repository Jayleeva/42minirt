#include "../inc/minirt.h"

int	hit_plane(const t_ray *r, const t_pl *pl, float tmin, float tmax, t_hit *out)
{
	t_vector	oc;
	float   t;
	float	a

	//	C = pl->coord
	//	X = r->o - pl->coord (ou oc?)
	//	P - pl->coord = r->d * t + (r->o - pl->coord ou oc?)
	//
	//	P = r->o + r->d * t
	oc = v_from_points(pl->coord, r->o); // calcule distance du point d'origine au sommet c du triangle (car 3 dim) = hypothemuse. = X
	
	(r->d *t + (r->o - pl->coord ou oc?)) v_dot() = 0;
	(D*t+X)|V = 0
	r->d v_dot() * t = -r->o - pl_coord ou oc? v_dot()
	D|V*t = -X|V
	t = - r->o - pl->coord ou oc? v_dot() / r->d v_dot()
	t = -X|V / D|V

	out->t = t;
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