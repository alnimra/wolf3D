/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:03:03 by mray              #+#    #+#             */
/*   Updated: 2018/02/26 14:03:03 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _WOLF_H
# define _WOLF_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <time.h>
# define WIDTH  3000
# define HEIGHT 1080



typedef	double		__attribute__((vector_size(2*sizeof(double))))	t_2dpt;
typedef	double		__attribute__((vector_size(3*sizeof(double))))	t_3dpt;
typedef	double		__attribute__((vector_size(4*sizeof(double))))	t_color;
typedef struct		s_obj
{
	void *obj;
	char *type;
}					t_obj;
t_obj				*create_obj(void *obj, char *type);
typedef struct		s_vec
{
	t_3dpt	comp[2];
}					t_vec;
typedef struct		s_cam
{
	t_3dpt	prop[4];
}					t_cam;
typedef struct		s_sphere
{
	t_3dpt			cnt;
	double			rad;
	t_color			col;
	double			(*find_insct)(struct s_sphere*, t_vec*);
}					t_sphere;
typedef struct		s_plane
{
	t_3dpt			normal;
	double			dist;
	t_color			col;
	double			(*find_insct)(struct s_plane*, t_vec*);
}					t_plane;
typedef struct		s_cyl
{
	t_vec		*vec;
	double		rad;
	t_color		col;
	double		(*find_insct)(struct s_cyl*, t_vec*);
}					t_cyl;
typedef struct		s_cone
{
	t_vec			*vec;
	double			tilt;
	t_color			col;
	double			(*find_insct)(struct s_cone*, t_vec*);
}					t_cone;
typedef struct		s_light
{
	t_3dpt		org;
	t_color		col;
}					t_light;
typedef struct		s_gl
{
	void			*lib;
	void			*surf;
	double			live_trans[5];
	double			trans_speed;
	double			ang_speed;
	int				**map;
	int				map_width;
	int				map_height;
	int				col_score;
	t_2dpt			pos;
	t_2dpt			dir;
	t_2dpt			cam_dir;
}					t_gl;
t_gl				*create_gl(void *lib, void *surf);
typedef struct		s_canvas
{
	void	*img;
	char	*pix_data;
	int		size_line;
	int		byte_size;
	int		endian;
}					t_canvas;
t_canvas			*create_canvas(t_gl *gl);
typedef struct		s_params
{
	void *p1;
	void *p2;
	void *p3;
}					t_params;
t_3dpt				create_3dpt(double x, double y, double z);
t_2dpt				create_2dpt(double x, double y);
void				set3dpt(t_3dpt *pt, double x, double y, double z);
double				angle_between(t_2dpt one, t_2dpt two);
double				squ(t_3dpt pt);
t_vec				*create_vec(t_3dpt org, t_3dpt dir);
void				set_vec(t_vec *v, t_3dpt org, t_3dpt dir);
t_cam				*create_cam(t_3dpt org, t_3dpt dir, t_3dpt right,
				t_3dpt down);
void				set_cam(t_cam *cam, double org_and_dir[3], double right[3],
				double down[3]);
t_color				create_color(double r, double g, double b, double special);
t_color				col_multi(t_color color, double scalar);
t_color				add_col(t_color color1, t_color color2);
t_color				multi_col(t_color color1, t_color color2);
t_color				avg_col(t_color color1, t_color color2);
void				correct_color_leaks(t_color *color);
t_light				*create_light(t_3dpt org, t_color col);
t_sphere			*create_sphere(t_3dpt cnt, double rad, t_color col);
t_3dpt				sphere_get_normal_at(t_sphere *sphere, t_3dpt pt);
t_plane				*create_plane(t_3dpt normal, double dist, t_color col);
void				store_pix(t_canvas *canvas, int x, int y, unsigned int c);
void				store_color_pix(t_canvas *canvas, int x, int y,
				t_color color);
void				scenify(t_gl *gl, t_canvas *canvas);
char				*read_in(char *filename);
void				parse_obj_data(t_gl *gl, char *data);
t_cyl				*create_cyl(t_3dpt org, t_3dpt dir, double rad,
				t_color col);
int		generate_random_hex(void);
t_3dpt				cyl_get_normal_at(t_cyl *cyl, t_3dpt pt);
t_cone				*create_cone(t_3dpt org, t_3dpt dir, double height,
				t_color col);
t_3dpt				cone_get_normal_at(t_cone *cone, t_3dpt pt);
void				parse_sphere(t_gl *gl, char ***obj_data, int j);
void				parse_cyl(t_gl *gl, char **obj_data, int j);
void				parse_cone(t_gl *gl, char **obj_data, int j);
void				parse_plane(t_gl *gl, char **obj_data, int j);
void				parse_light(t_gl *gl, char **obj_data, int j);
void				parse_cam(t_gl *gl, char **obj_data, int j);
void				errorify(char *str);
int					is_visi_obj(char *str);
int					get_num_of_visi_objs(t_gl *gl);
int					get_num_of_lights(t_gl *gl);
int					get_winning_obj(double *intersections, int size);
double				find_inscts(t_obj **objs, int i, t_vec *v);
t_color				get_color(t_obj **objs, int i);
t_3dpt				get_normal_at(t_obj **objs, int i, t_3dpt pt);
t_color				get_color_at(t_gl *gl);
double				solve_for_roots(double coef[3]);
int					get_num_of_args(char **str);
void				error_if_not(char **str, int i);
int					key_handler(int key, t_params *para);
void				add_sun(t_canvas *canvas);
void				reset_canvas(t_canvas *canvas);
void				put_game_over(t_gl *gl, t_canvas *canvas);
void				efla_e(t_canvas *canvas, t_2dpt pt_i, t_2dpt pt_f, int color);
#endif
