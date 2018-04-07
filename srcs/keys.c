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

void	left_key(t_gl *gl)
{
	double tmp_coord;

	tmp_coord = gl->dir[0];
	gl->dir[0] =
		gl->dir[0] * cos(gl->ang_speed) - gl->dir[1] * sin(gl->ang_speed);
	gl->dir[1] =
		tmp_coord * sin(gl->ang_speed) + gl->dir[1] * cos(gl->ang_speed);
	tmp_coord = gl->cam_dir[0];
	gl->cam_dir[0] = gl->cam_dir[0] * cos(gl->ang_speed) -
					gl->cam_dir[1] * sin(gl->ang_speed);
	gl->cam_dir[1] =
		tmp_coord * sin(gl->ang_speed) + gl->cam_dir[1] * cos(gl->ang_speed);
}

void	right_key(t_gl *gl)
{
	double tmp_coord;

	tmp_coord = gl->dir[0];
	gl->dir[0] =
		gl->dir[0] * cos(-gl->ang_speed) - gl->dir[1] * sin(-gl->ang_speed);
	gl->dir[1] =
		tmp_coord * sin(-gl->ang_speed) + gl->dir[1] * cos(-gl->ang_speed);
	tmp_coord = gl->cam_dir[0];
	gl->cam_dir[0] = gl->cam_dir[0] * cos(-gl->ang_speed) -
					gl->cam_dir[1] * sin(-gl->ang_speed);
	gl->cam_dir[1] =
		tmp_coord * sin(-gl->ang_speed) + gl->cam_dir[1] * cos(-gl->ang_speed);
}

void	up_key(t_gl *gl)
{
	if (!(gl->map[(int)(gl->pos[0] + gl->dir[0] * gl->trans_speed)]
				[(int)(gl->pos[1])]))
		gl->pos[0] += gl->dir[0] * gl->trans_speed;
	else if (gl->map[(int)(gl->pos[0] + gl->dir[0] * gl->trans_speed)]
					[(int)(gl->pos[1])] == 4)
		gl->col_score -= 1;
	if (!(gl->map[(int)(gl->pos[0])]
				[(int)(gl->pos[1] + gl->dir[1] * gl->trans_speed)]))
		gl->pos[1] += gl->dir[1] * gl->trans_speed;
	else if (gl->map[(int)(gl->pos[0])]
					[(int)(gl->pos[1] + gl->dir[1] * gl->trans_speed)] == 4)
		gl->col_score -= 1;
}

void	down_key(t_gl *gl)
{
	if (!(gl->map[(int)(gl->pos[0] - gl->dir[0] * gl->trans_speed)]
				[(int)(gl->pos[1])]) &&
		gl->pos[0] > 0)
		gl->pos[0] -= gl->dir[0] * gl->trans_speed;
	else if (gl->map[(int)(gl->pos[0] - gl->dir[0] * gl->trans_speed)]
					[(int)(gl->pos[1])] == 4)
		gl->col_score -= 1;
	if (!(gl->map[(int)(gl->pos[0])]
				[(int)(gl->pos[1] - gl->dir[1] * gl->trans_speed)]) &&
		gl->pos[1] > 0)
		gl->pos[1] -= gl->dir[1] * gl->trans_speed;
	else if (gl->map[(int)(gl->pos[0])]
					[(int)(gl->pos[1] - gl->dir[1] * gl->trans_speed)] == 4)
		gl->col_score -= 1;
}

int		key_handler(int key, t_params *para)
{
	t_gl		*gl;
	t_canvas	*canvas;

	gl = para->p1;
	canvas = para->p2;
	if (key == 123)
		left_key(gl);
	if (key == 124)
		right_key(gl);
	if (key == 126)
		up_key(gl);
	if (key == 125)
		down_key(gl);
	if (key == 53)
		exit(1);
	if (gl->col_score > 0)
	{
		reset_canvas(canvas);
		scenify(gl, canvas);
		mlx_string_put(gl->lib, gl->surf, 0, 0, 0xFFFFFF, "Penalty Score: ");
		mlx_string_put(gl->lib, gl->surf, 200, 0, 0, ft_itoa(gl->col_score));
	}
	else
		put_game_over(gl, canvas);
	return (0);
}
