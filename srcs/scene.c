/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 12:14:14 by mray              #+#    #+#             */
/*   Updated: 2018/03/15 12:14:14 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		generate_random_hex(void)
{
	int x;

	x = rand() & 0xff;
	x |= (rand() & 0xff) << 8;
	x |= (rand() & 0xff) << 16;
	x |= (rand() & 0xff) << 24;
	return (x * 2 & 0xffffff);
}

int		select_color(t_gl *gl, int map[2])
{
	int color_ret;

	color_ret = 0x0000FF;
	if (gl->map[map[0]][map[1]] == 4)
		color_ret = generate_random_hex();
	else if (gl->map[map[0]][map[1]] == 2)
		color_ret = 0x01FF00;
	else if (gl->map[map[0]][map[1]] > 2)
		color_ret = 0x0000FF;
	if (gl->side_of_contact == 1)
		color_ret /= 2;
	return (color_ret);
}

t_2dpt	abs_2dpt(t_2dpt pt)
{
	return ((t_2dpt){fabs(pt[0]), fabs(pt[1])});
}

void	calc_line_start_end(t_gl *gl, int *line_height, int *draw_start,
					int *draw_end)
{
	(*line_height) = (int)((1 / gl->dist_to_wall) * HEIGHT);
	(*draw_start) = -(*line_height) / 2 + (HEIGHT / 2);
	if ((*draw_start) < 0)
		(*draw_start) = 0;
	(*draw_end) = (*line_height) / 2 + (HEIGHT / 2);
	if ((*draw_end) >= HEIGHT || (*draw_end) < 0)
		(*draw_end) = HEIGHT - 1;
}

void	scenify(t_gl *gl, t_canvas *canvas)
{
	int x;
	int map[2];
	int line_height;
	int draw_start;
	int draw_end;

	x = -1;
	while (++x < WIDTH)
	{
		init_ray(gl, map, x);
		cast_ray_till_intersection(gl, map);
		if (gl->side_of_contact == 0)
			gl->dist_to_wall =
				(map[0] - gl->pos[0] + (1 - gl->arr_step[0]) / 2) / gl->ray[0];
		else
			gl->dist_to_wall =
				(map[1] - gl->pos[1] + (1 - gl->arr_step[1]) / 2) / gl->ray[1];
		calc_line_start_end(gl, &line_height, &draw_start, &draw_end);
		efla_e(canvas, (t_2dpt){x, draw_start}, (t_2dpt){x, draw_end},
			select_color(gl, map));
	}
	mlx_put_image_to_window(gl->lib, gl->surf, canvas->img, 0, 0);
}
