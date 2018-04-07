/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pix.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 15:11:41 by mray              #+#    #+#             */
/*   Updated: 2018/03/24 15:11:41 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	store_pix(t_canvas *canvas, int x, int y, unsigned int c)
{
	int i;

	i = (x * 4) + (y * canvas->size_line);
	*(canvas->pix_data + i) = c;
	*(canvas->pix_data + i + 1) = c >> 8;
	*(canvas->pix_data + i + 2) = c >> 16;
}
