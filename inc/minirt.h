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

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}		t_rgb;

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}			t_point;

typedef struct s_vector
{
	float	o_x;
	float	o_y;
	float	o_z;
}			t_vector;

typedef struct s_A
{
	float	ratio;
	t_rgb	colors;
}			t_A;

typedef struct s_C
{
	t_point		coord;
	t_vector	ornt;
	int			fov;
}				t_C;

typedef struct s_L
{
	t_point		coord;
	float		ratio;
}				t_L;

typedef struct s_sp
{
	t_point		coord;
	float		diameter;
	t_rgb		colors;
}				t_sp;

typedef struct s_pl
{
	t_point		coord;
	t_vector	ornt;
	t_rgb		colors;
}				t_pl;

typedef struct s_cy
{
	t_point		coord;
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

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_pixel		*canvas;
	char		**map;
	char		*used;
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
}				t_data;

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
int		check_coord(t_point *coord, char *s);
int		check_ornt(t_vector *ornt, char *s);
int		check_ratio(float *ratio_, char *s);
int		check_diameter_or_height(float *len_, char *s);

//ray tracing
int 	ray_tracing(t_data *data);
void	cast_ray(t_data *data, int i, int x, int y);
int 	compute_intersections(t_data *data, int x, int y);
void	set_color(t_data *data, int x, int y);

//utils
int		count_elem(t_data *data, int fd);
int		increment_elem(t_data *data, char *line);
int		alloc_lel(t_data *data);
int		is_already_used(char *used, char c);
int		is_usable(char *line, char *used, int i);
int		is_n_uel_valid(t_data *data);
void	free_big_tab(char ***bigtab);

#endif