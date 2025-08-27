#ifndef MINIRT_H
# define MINIRT_H 
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

typedef struct s_rgb
{
	int R;
	int G;
	int B;
}       t_rgb;

typedef struct s_point
{
	float   x;
	float   y;
	float   z;
}           t_point;

typedef struct s_vector
{
	float   o_x;
	float   o_y;
	float   o_z;
}           t_vector;

typedef struct s_A
{
	float   ratio;
	t_rgb   colors;
}           t_A;

typedef struct s_C
{
	t_point     coord;
	t_vector    ornt;
	int         fov;
}               t_C;

typedef struct s_L
{
	t_point     coord;
	float       ratio;
}               t_L;

typedef struct s_sp
{
	t_point     coord;
	float       diameter;
	t_rgb       colors;
}               t_sp;

typedef struct s_pl
{
	t_point     coord;
	t_vector    ornt;
	t_rgb       colors;
}               t_pl;

typedef struct s_cy
{
	t_point     coord;
	t_vector    ornt;
	float       diameter;
	float       height;
	t_rgb       colors;
}               t_cy;

typedef struct s_data
{
	void    *mlx_ptr;
	void	*win_ptr;
	char	***map;
	int		index;
	t_A		A;
	t_C		C;
	t_L		L;
	t_sp	sp;
	t_pl	pl;
	t_cy	cy;
}           t_data;

//essentials
void	init(t_data *data);
void	initialize(t_data *data, size_t len, int nelem);
int	    on_destroy(t_data *data);

//parsing
int 	is_valid(t_data *data, char *s);
int 	is_map_valid(t_data *data, int fd, int nelem);

//check config
int 	check_config(t_data *data, char *el);
int 	check_A(t_data *data, char *A);
int 	check_C(t_data *data, char *C);
int 	check_L(t_data *data, char *L);

//utils
int 	count_elem(int fd);
int		alloc_ptr(char ***map, char *used, int nelem);
int 	is_already_used(char *used, char c);
int		is_usable(char *line, char *used, int i);
int		is_element_missing(char *used);
void	free_big_tab(char ***bigtab);

#endif