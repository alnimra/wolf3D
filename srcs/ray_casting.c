/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 19:08:03 by mray              #+#    #+#             */
/*   Updated: 2018/04/06 19:08:03 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
** Credits to Lodev for code concept and reference
*/

void	setup_ray(t_gl *gl, int map[2])
{
	if (gl->ray[0] < 0)
	{
		gl->arr_step[0] = -1;
		gl->side_dist[0] = (gl->pos[0] - map[0]) * gl->increment_dist[0];
	}
	else
	{
		gl->arr_step[0] = 1;
		gl->side_dist[0] = (map[0] + gl->d4 - gl->pos[0]) *
		gl->increment_dist[0];
	}
	if (gl->ray[1] < 0)
	{
		gl->arr_step[1] = -1;
		gl->side_dist[1] = (gl->pos[1] - map[1]) * gl->increment_dist[1];
	}
	else
	{
		gl->arr_step[1] = 1;
		gl->side_dist[1] = (map[1] + 1.0 - gl->pos[1]) * gl->increment_dist[1];
	}
}

void	init_ray(t_gl *gl, int map[2], int x)
{
	gl->camera_x = 2 * x / (double)WIDTH - 1;
	gl->ray = gl->dir + (gl->cam_dir * (t_2dpt){gl->camera_x, gl->camera_x});
	map[0] = (int)gl->pos[0];
	map[1] = (int)gl->pos[1];
	gl->increment_dist = abs_2dpt(((t_2dpt){1, 1}) / gl->ray);
	gl->inter = 0;
	setup_ray(gl, map);
}

void	cast_ray_till_intersection(t_gl *gl, int map[2])
{
	while (gl->inter == 0)
	{
		if (gl->side_dist[0] < gl->side_dist[1])
		{
			gl->side_dist[0] += gl->increment_dist[0];
			map[0] += gl->arr_step[0];
			gl->side_of_contact = 0;
		}
		else
		{
			gl->side_dist[1] += gl->increment_dist[1];
			map[1] += gl->arr_step[1];
			gl->side_of_contact = 1;
		}
		if (map[0] >= gl->map_height || map[1] >= gl->map_width || map[0] < 0 ||
			map[1] < 0)
			errorify("That was a dangerous map, we can't let you fall of a "
					"cliff, make a safer map yo.");
		if (gl->map[map[0]][map[1]] > 0)
			gl->inter = 1;
	}
}
