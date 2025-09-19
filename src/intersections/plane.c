#include "../inc/minirt.h"

int	hit_plane(const t_ray *r, const t_pl *pl, float tmin, float tmax, t_hit *out)
{
    out->kind = PLANE;
    return (1);
}