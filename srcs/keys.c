/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 15:28:39 by mray              #+#    #+#             */
/*   Updated: 2018/04/01 15:28:39 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
//TEST5
int key_handler(int key, t_params *para)
{
	t_gl		*gl;
	t_canvas	*canvas;
	double		tmp_coord;

	gl = para->p1;
	canvas = para->p2;
	if (key == 123)
	{
		tmp_coord = gl->dir[0];
		// USE vector extnations math
		gl->dir[0] =
			gl->dir[0] * cos(gl->ang_speed) - gl->dir[1] * sin(gl->ang_speed);
		gl->dir[1] =
			tmp_coord * sin(gl->ang_speed) + gl->dir[1] * cos(gl->ang_speed);
		tmp_coord = gl->cam_dir[0];
		gl->cam_dir[0] = gl->cam_dir[0] * cos(gl->ang_speed) -
						 gl->cam_dir[1] * sin(gl->ang_speed);
		gl->cam_dir[1] = tmp_coord * sin(gl->ang_speed) +
						 gl->cam_dir[1] * cos(gl->ang_speed);
	}
	if (key == 124)
	{
		tmp_coord = gl->dir[0];
		// USE vector extensions math
		gl->dir[0] =
			gl->dir[0] * cos(-gl->ang_speed) - gl->dir[1] * sin(-gl->ang_speed);
		gl->dir[1] =
			tmp_coord * sin(-gl->ang_speed) + gl->dir[1] * cos(-gl->ang_speed);
		tmp_coord = gl->cam_dir[0];
		gl->cam_dir[0] = gl->cam_dir[0] * cos(-gl->ang_speed) -
						 gl->cam_dir[1] * sin(-gl->ang_speed);
		gl->cam_dir[1] = tmp_coord * sin(-gl->ang_speed) +
						 gl->cam_dir[1] * cos(-gl->ang_speed);
	}
	if (key == 126)
	{
		if (!(gl->map[(int)(gl->pos[0] + gl->dir[0] * gl->trans_speed)]
					 [(int)(gl->pos[1])]))
			gl->pos[0] += gl->dir[0] * gl->trans_speed;
		else if(gl->map[(int)(gl->pos[0] + gl->dir[0] * gl->trans_speed)]
					 [(int)(gl->pos[1])] == 4)
			gl->col_score -= 1;
		if (!(gl->map[(int)(gl->pos[0])]
					 [(int)(gl->pos[1] + gl->dir[1] * gl->trans_speed)]))
			gl->pos[1] += gl->dir[1] * gl->trans_speed;
		else if(gl->map[(int)(gl->pos[0])]
					 [(int)(gl->pos[1] + gl->dir[1] * gl->trans_speed)] == 4)
			gl->col_score -= 1;
	}
	else if (key == 125)
	{
		if (!(gl->map[(int)(gl->pos[0] - gl->dir[0] * gl->trans_speed)]
					 [(int)(gl->pos[1])]) &&
			gl->pos[0] > 0)
			gl->pos[0] -= gl->dir[0] * gl->trans_speed;
		else if(gl->map[(int)(gl->pos[0] - gl->dir[0] * gl->trans_speed)]
					 [(int)(gl->pos[1])] == 4)
			gl->col_score -= 1;
		if (!(gl->map[(int)(gl->pos[0])]
					 [(int)(gl->pos[1] - gl->dir[1] * gl->trans_speed)]) &&
			gl->pos[1] > 0)
			gl->pos[1] -= gl->dir[1] * gl->trans_speed;
		else if(gl->map[(int)(gl->pos[0])]
					 [(int)(gl->pos[1] - gl->dir[1] * gl->trans_speed)] == 4)
			gl->col_score -= 1;
	}
	if(key == 53)
		exit(1);
	if (gl->col_score > 0)
	{
		reset_canvas(canvas);
		scenify(gl, canvas);
		mlx_string_put(gl->lib, gl->surf, 0, 0, 0xFFFFFF, "Penalty Score: ");
		mlx_string_put(gl->lib, gl->surf, 200, 0, 0xFFFFFF,
				ft_itoa(gl->col_score));
	}else
		put_game_over(gl, canvas);

	ft_putnbr(key);
	ft_putchar('\n');
	return (0);
}
