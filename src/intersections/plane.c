#include "../inc/minirt.h"

int	hit_plane(const t_ray *r, const t_pl *pl, float tmin, float tmax, t_hit *out)
{
    t_vector	oc;
    float   t;

    oc = v_from_points(pl->coord, r->o); // calcule distance du point d'origine au sommet c du triangle (car 3 dim) = hypothemuse.

    out->t = t;
    out->kind = PLANE;
    return (1);
}