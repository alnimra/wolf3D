/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:38:19 by mray              #+#    #+#             */
/*   Updated: 2018/02/26 16:38:19 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_gl		*create_gl(void *lib, void *surf)
{
	t_gl	*tmp;

	tmp = ft_memalloc(sizeof(t_gl));
	tmp->lib = lib;
	tmp->surf = surf;
	tmp->trans_speed = 0.15;
	tmp->ang_speed =  0.08;
	tmp->pos = (t_2dpt){-1, -1};
	tmp->dir = (t_2dpt){-1, 0};
	tmp->cam_dir = (t_2dpt){0, 0.66};
	tmp->col_score = 100;
	return (tmp);
}

t_canvas	*create_canvas(t_gl *gl)
{
	t_canvas *tmp;

	tmp = ft_memalloc(sizeof(t_canvas));
	tmp->img = mlx_new_image(gl->lib, WIDTH, HEIGHT);
	tmp->pix_data = mlx_get_data_addr(tmp->img, &(tmp->byte_size),
&(tmp->size_line), &(tmp->endian));
	return (tmp);
}
