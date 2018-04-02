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

int select_color(t_gl *gl, int map[2], int side)
{
	int color_ret;
	color_ret = 0x0000FF;
	if(gl->map[map[0]][map[1]] == 4)
		color_ret = generate_random_hex();
		// color_ret = 0xFF0000;
	else if(gl->map[map[0]][map[1]] == 2)
		color_ret = 0x01FF00;
	else if(gl->map[map[0]][map[1]] > 2)
		color_ret = 0x0000FF;
// else if(gl->map[map[0]][map[1]] == 7)
	if(side == 1)
		color_ret /= 2;
	return (color_ret);
}

t_2dpt		abs_2dpt(t_2dpt pt)
{
	return ((t_2dpt){fabs(pt[0]), fabs(pt[1])});
}

void	scenify(t_gl *gl, t_canvas *canvas)
{
		int x = -1;

		while(++x < WIDTH)
		{
			double camera_x = 2 * x / (double)WIDTH - 1;
			t_2dpt cam_x = (t_2dpt){camera_x, camera_x};
			// t_2dpt ray_dir = create_3dpt(gl->dir[0] + gl->cam_dir[0] * camera_x, gl->dir[1] + gl->cam_dir[1] * camera_x, 0);
			t_2dpt ray_dir = gl->dir + (gl->cam_dir * cam_x);

			int map[2] = {(int)gl->pos[0], (int)gl->pos[1]};

			t_2dpt side_dist;
			t_2dpt delta_dist;
			// t_2dpt delta_dist = create_3dpt(abs(1/ray_dir[0]), abs(1/ray_dir[1]));
			delta_dist = abs_2dpt(((t_2dpt){1, 1}) / ray_dir);
			double perp_wall_dist;
			int step[2];

			int is_contact = 0;
			int side;
			if(ray_dir[0] < 0)
			{
				step[0] = -1;
				side_dist[0] = (gl->pos[0] - map[0]) * delta_dist[0];
			}else{
				step[0] = 1;
				side_dist[0] = (map[0] + 1.0 - gl->pos[0]) * delta_dist[0];
			}
			if(ray_dir[1] < 0)
			{
				step[1] = -1;
				side_dist[1] = (gl->pos[1] - map[1]) * delta_dist[1];
			}else{
				step[1] = 1;
				side_dist[1] = (map[1] + 1.0 - gl->pos[1]) * delta_dist[1];
			}

			while(is_contact == 0)
			{
				if(side_dist[0] < side_dist[1])
				{
					side_dist[0] += delta_dist[0];
					map[0] += step[0];
					side = 0;
				}else {
					side_dist[1] += delta_dist[1];
					map[1]  += step[1];
					side = 1;
				}
				if(map[0] >= gl->map_height || map[1] >= gl->map_width || map[0] < 0 || map[1] < 0)
					errorify("That was a dangerous map, we can't let you fall of a cliff, make a safer map yo.");
				if(gl->map[map[0]][map[1]] > 0)
					is_contact = 1;
			}
			if(side == 0)
				perp_wall_dist = (map[0] - gl->pos[0] + (1 - step[0]) / 2) / ray_dir[0];
			else
				perp_wall_dist = (map[1] - gl->pos[1] + (1 - step[1]) / 2) / ray_dir[1];
			int line_height = (int)((1 / perp_wall_dist)* HEIGHT );
			int draw_start = -line_height / 2 + (HEIGHT / 2);
			if(draw_start < 0) draw_start = 0;
			int draw_end = line_height / 2 + (HEIGHT / 2);
			if(draw_end >= HEIGHT || draw_end < 0) draw_end = HEIGHT - 1;
				efla_e(canvas, (t_2dpt){x, draw_start}, (t_2dpt){x, draw_end}, select_color(gl, map, side));
		}
	// }


	mlx_put_image_to_window(gl->lib, gl->surf, canvas->img, 0, 0);
}
