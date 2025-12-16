#include "../inc/minirt.h"

// Crée un vecteur à partir de 3 floats
static t_vector	v_make(float x, float y, float z)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

static void	cam_build_basis(t_data *d)
{
	t_vector	up;
	t_vector	dir;
	t_vector	tmp;

	up = v_make(0.0f, 1.0f, 0.0f);
	dir = v_norm(d->c.ornt);
	d->view.w = dir;
	if (fabsf(v_dot(dir, up)) > 0.999f)
		up = v_make(0.0f, 0.0f, 1.0f);
	tmp = v_cross(up, dir);
	d->view.u = v_norm(tmp);
	d->view.v = v_cross(dir, d->view.u);
}

void	cam_prepare_view(t_data *d)
{
	float	aspect;
	float	vh;
	float	vfov;

	aspect = (float)W_WIDTH / (float)W_HEIGHT;
	vfov = (float)d->c.fov * (float)M_PI / 180.0f;
	vh = 2.0f * tanf(vfov * 0.5f);
	d->view.half_h = vh * 0.5f;
	d->view.half_w = d->view.half_h * aspect;
	cam_build_basis(d);
}

static t_vector	compute_dir(t_camview view, int x, int y)
{
	t_vector	dir;
	float		u;
	float		v;

	u = ((((float)x + 0.5f) / (float)W_WIDTH) - 0.5f) * (2.0f * view.half_w);
	v = (0.5f - (((float)y + 0.5f) / (float)W_HEIGHT)) * (2.0f * view.half_h);
	dir = v_add(v_add(v_scale(view.u, u), v_scale(view.v, v)), view.w);
	return (dir);
}

t_ray	make_primary_ray(t_data *d, int x, int y)
{
	t_ray	r;

	r.o = d->c.coord;
	r.d = v_norm(compute_dir(d->view, x, y));
	return (r);
}
