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

# define WIDTH 3000
# define HEIGHT 1080

typedef	double		__attribute__((vector_size(2*sizeof(double))))	t_2dpt;

typedef struct		s_gl
{
	void			*lib;
	void			*surf;
	double			live_trans[5];
	double			trans_speed;
	double			ang_speed;
	double			camera_x;
	double			dist_to_wall;
	double			d4;
	int				**map;
	int				map_width;
	int				map_height;
	int				col_score;
	int				stored_width;
	int				side_of_contact;
	int				arr_step[2];
	int				inter;
	t_2dpt			increment_dist;
	t_2dpt			pos;
	t_2dpt			dir;
	t_2dpt			cam_dir;
	t_2dpt			side_dist;
	t_2dpt			delta_dist;
	t_2dpt			ray;
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

void				store_pix(t_canvas *canvas, int x, int y, unsigned int c);
void				scenify(t_gl *gl, t_canvas *canvas);
char				*read_in(char *filename);
void				parse_obj_data(t_gl *gl, char *data);
int					generate_random_hex(void);
void				errorify(char *str);
int					key_handler(int key, t_params *para);
void				add_sun(t_canvas *canvas);
void				reset_canvas(t_canvas *canvas);
void				put_game_over(t_gl *gl, t_canvas *canvas);
void				efla_e(t_canvas *canvas, t_2dpt pt_i, t_2dpt pt_f,
											int color);
void				get_the_data(t_gl *gl, char *object_string_data, int *width,
				  							int i);
int					get_double_char_size(char **double_char);
void				store_map_row(t_gl *gl, char **map_row, int i);
void				setup_ray(t_gl *gl, int map[2]);
void				init_ray(t_gl *gl, int map[2], int x);
void				cast_ray_till_intersection(t_gl *gl, int map[2]);
t_2dpt				abs_2dpt(t_2dpt pt);
#endif
