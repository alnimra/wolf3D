/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:42:51 by mray              #+#    #+#             */
/*   Updated: 2018/03/08 15:43:00 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
** Credits to Po-Han Lin for EFLA_E
** http://www.edepot.com/algorithm.html
*/

void	y_longer(t_canvas *canvas, t_2dpt pt_i, int para[7])
{
	if (para[3] > 0)
	{
		para[3] += pt_i[1];
		para[6] = 0x8000 + ((int)pt_i[0] << 16);
		while (pt_i[1] <= para[3])
		{
			store_pix(canvas, para[6] >> 16, pt_i[1], para[0]);
			para[6] += para[4];
			++pt_i[1];
		}
		return ;
	}
	para[3] += pt_i[1];
	para[6] = 0x8000 + ((int)pt_i[0] << 16);
	while (pt_i[1] >= para[3])
	{
		store_pix(canvas, para[6] >> 16, pt_i[1], para[0]);
		para[6] -= para[4];
		--pt_i[1];
	}
	return ;
}

void	y_not_longer(t_canvas *canvas, t_2dpt pt_i, int para[7])
{
	if (para[3] > 0)
	{
		para[3] += pt_i[0];
		para[6] = 0x8000 + ((int)pt_i[1] << 16);
		while (pt_i[0] <= para[3])
		{
			store_pix(canvas, pt_i[0], para[6] >> 16, para[0]);
			para[6] += para[4];
			++pt_i[0];
		}
		return ;
	}
	para[3] += pt_i[0];
	para[6] = 0x8000 + ((int)pt_i[1] << 16);
	while (pt_i[0] >= para[3])
	{
		store_pix(canvas, pt_i[0], para[6] >> 16, para[0]);
		para[6] -= para[4];
		--pt_i[0];
	}
}

/*
** para[0] = color, para[1] = y_longer, para[2] = shortLen, para[3] = longLen,
** para[4] = decInc, para[5] = swap, para[6] = j
*/

void	efla_e(t_canvas *canvas, t_2dpt pt_i, t_2dpt pt_f, int color)
{
	int para[7];

	para[0] = color;
	para[1] = 0;
	para[2] = pt_f[1] - pt_i[1];
	para[3] = pt_f[0] - pt_i[0];
	if (abs(para[2]) > abs(para[3]))
	{
		para[5] = para[2];
		para[2] = para[3];
		para[3] = para[5];
		para[1] = 1;
	}
	if (para[3] == 0)
		para[4] = 0;
	else
		para[4] = (para[2] << 16) / para[3];
	if (para[1])
		return (y_longer(canvas, pt_i, para));
	return (y_not_longer(canvas, pt_i, para));
}
