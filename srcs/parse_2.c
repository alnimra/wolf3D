/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 11:44:54 by mray              #+#    #+#             */
/*   Updated: 2018/04/06 11:44:54 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	get_the_data(t_gl *gl, char *object_string_data, int *width,
			int i)
{
	char **map_row;

	map_row = ft_strsplit(object_string_data, ',');
	if (gl->stored_width == 0)
	{
		gl->map_width = get_double_char_size(map_row);
		*width = gl->map_width;
		gl->stored_width = 1;
	}
	else
		*width = get_double_char_size(map_row);
	if (*width != gl->map_width)
		errorify("Bad Map, width not aligned");
	store_map_row(gl, map_row, i);
	free_array((void **)map_row);
}
