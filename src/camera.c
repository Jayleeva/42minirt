#include "../inc/minirt.h"

static void	cam_build_basis(t_data *d)
{
	t_vector up;
	t_vector dir;
	t_vector tmp;

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
	float aspect;
	float vh;
	float vfov;

	aspect = (float)W_WIDTH / (float)W_HEIGHT;
	vfov = (float)d->c.fov * (float)M_PI / 180.0f;
	vh = 2.0f * tanf(vfov * 0.5f);
	d->view.half_h = vh * 0.5f;
	d->view.half_w = d->view.half_h * aspect;
	cam_build_basis(d);
}

t_ray	make_primary_ray(t_data *d, int x, int y)
{
	t_ray r;
	float u;
	float v;
	t_vector dir;
	float fx;
	float fy;

	fx = ((float)x + 0.5f) / (float)W_WIDTH;
	fy = ((float)y + 0.5f) / (float)W_HEIGHT;
	u = (fx - 0.5f) * (2.0f * d->view.half_w);
	v = (0.5f - fy) * (2.0f * d->view.half_h);
	dir = v_add(v_add(v_scale(d->view.u, u), v_scale(d->view.v, v)), d->view.w);
	r.o = d->c.coord;
	r.d = v_norm(dir);
	return (r);
}
