#ifndef MINIRT_H
# define MINIRT_H 
# define M_PI 3.14159265358979323846
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <sys/time.h>
# include "libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

# define K_Q 113
# define K_ESC 65307

# define W_WIDTH 1280
# define W_HEIGHT 720

# define EPS 1e-3f

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
	float	s_r;
	float	s_g;
	float	s_b;
}			t_rgb;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}			t_vector;

typedef struct s_A
{
	float	ratio;
	t_rgb	colors;
}			t_A;

typedef struct s_C
{
	t_vector	coord;
	t_vector	ornt;
	int			fov;
}				t_C;

typedef struct s_L
{
	t_vector	coord;
	float		ratio;
}				t_L;

typedef struct s_sp
{
	t_vector	coord;
	float		diameter;
	t_rgb		colors;
}				t_sp;

typedef struct s_pl
{
	t_vector	coord;
	t_vector	ornt;
	t_rgb		colors;
}				t_pl;

typedef struct s_cy
{
	t_vector	coord;
	t_vector	ornt;
	float		diameter;
	float		height;
	t_rgb		colors;
}				t_cy;

typedef struct s_pixel
{
	t_rgb		colors;
	int			color;
	int			x;
	int			y;
}				t_pixel;

typedef struct s_img_data
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		size;
	int		endian;
}			t_img_data;

typedef struct s_camview {
	t_vector	u;
	t_vector	v;
	t_vector	w;
	float		half_w;
	float		half_h;
}				t_camview;

typedef struct s_specular
{
	float	ks;
	float	shiny;
}			t_specular;


typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_pixel		*canvas;
	char		**map;
	char		*used;
	t_img_data	img;
	int			index;
	int			nelem;
	int			n_uel[3];
	t_A			a;
	t_C			c;
	t_L			l;
	int			n_lel[3];
	int			i_sp;
	int			i_pl;
	int			i_cy;
	t_sp		*sp;
	t_pl		*pl;
	t_cy		*cy;
	t_camview	view;
	t_specular	spec;
}				t_data;

typedef enum s_shape_type
{
	SPHERE,
	PLANE,
	CYLINDER,
}	t_shape_type;

typedef struct s_hit
{
	float		t;
	t_vector	p;
	t_vector	n;
	int			kind;
	int			idx;
}				t_hit;

typedef struct s_ray {
	t_vector	o;
	t_vector	d;
}				t_ray;

typedef struct s_cap {
	t_vector	center;
	t_vector	normal;
	float		radius;
} 				t_cap;



//essentials
void	init(t_data *data);
int		fill_map(t_data *data, int i);
void	window(t_data *data);
int		on_destroy(t_data *data);

//parsing
int		is_valid(t_data *data, char *s);
int		first_open(t_data *data, char *s);
int		is_map_valid(t_data *data, int fd);

//check config
int		check_config(t_data *data, char *el);

int		check_a(t_data *data, char *type);
int		check_c(t_data *data, char *type);
int		check_l(t_data *data, char *type);
int		check_fov(int *fov_, char *s);

int		check_sp(t_data *data, char *sp);
int		check_pl(t_data *data, char *pl);
int		check_cy(t_data *data, char *cy);

int		check_colors(t_rgb *colors, char *s);
int		check_coord(t_vector *coord, char *s);
int		check_ornt(t_vector *ornt, char *s);
int		check_ratio(float *ratio_, char *s);
int		check_diameter_or_height(float *len_, char *s);

//check config utils
int		count_elem(t_data *data, int fd);
int		increment_elem(t_data *data, char *line);
int		alloc_lel(t_data *data);
int		is_already_used(char *used, char c);
int		is_usable(char *line, char *used, int i);
int		is_n_uel_valid(t_data *data);

//rgb to hex
int		rgb_to_hex(t_rgb *colors);
void	rgb_to_hex_utils(int *tmp, int n, char *s);
int		get_n(int *tmp);

//colors
void	rgb_rescale(t_rgb *color, int type);
void	initialize_color(t_data *data, t_pixel *canvas);

//ray tracing
float	compute_specular(t_data *d, t_hit *h, t_vector n);
float	compute_diffuse(t_data *d, t_hit *h, t_vector n);
t_rgb	compute_lighting(t_data *d, t_hit *h, t_rgb obj);
void 	ft_put_pixel(t_img_data *data, int x, int y, int color);
void	loop_on_pixels(t_data *d);
int 	ray_tracing(t_data *data);
void	cast_ray(t_data *data, int i, int x, int y);
int 	compute_intersections(t_data *data, int x, int y);
void	set_color(t_data *data, int x, int y);
void	cam_prepare_view(t_data *d);
t_ray	make_primary_ray(t_data *d, int x, int y);

// vectors
t_vector	v_add(t_vector a, t_vector b);
t_vector	v_sub(t_vector a, t_vector b);
t_vector	v_scale(t_vector a, float k);
t_vector	v_cross(t_vector a, t_vector b);
float		v_dot(t_vector a, t_vector b);

t_vector	v_norm(t_vector a);
float		v_len(t_vector a);
float		v_len2(t_vector a);

//intersections
int	hit_sphere(const t_ray *r, const t_sp *s, float tmin, float tmax, t_hit *out);
int	hit_cylinder(const t_ray *r, const t_cy *cy,
						float tmin, t_hit *out);
int	hit_plane(const t_ray *r, const t_pl *pl, float tmin, float tmax, t_hit *out);
int	world_hit(t_data *d, const t_ray *r, float tmin, float tmax, t_hit *h);
int world_hit_shadow(t_data *d, const t_ray *r, float tmin, float tmax, t_hit *h);


#endif