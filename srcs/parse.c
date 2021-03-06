/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 12:57:38 by mray              #+#    #+#             */
/*   Updated: 2018/03/18 12:57:38 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	errorify(char *str)
{
	ft_putstr(str);
	exit(1);
}

char	*read_in(char *filename)
{
	int		fd;
	int		byte_size;
	char	*str;
	char	*line;
	char	*tmp;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		errorify("File opening error");
	str = ft_strdup("");
	line = NULL;
	while ((byte_size = get_next_line(fd, &line) > 0))
	{
		tmp = line;
		line = ft_strjoin(line, "\n");
		ft_memdel((void **)&tmp);
		tmp = str;
		str = ft_strjoin(str, line);
		ft_memdel((void **)&tmp);
		if (line)
			ft_memdel((void **)&line);
	}
	if (line)
		ft_memdel((void **)&line);
	return (str);
}

int		get_double_char_size(char **double_char)
{
	int i;

	i = 0;
	while (double_char[i])
		i++;
	return (i);
}

void	store_map_row(t_gl *gl, char **map_row, int i)
{
	int j;

	gl->map[i] = (int*)ft_memalloc(sizeof(int) * gl->map_width);
	j = -1;
	while (++j < gl->map_width)
	{
		gl->map[i][j] = ft_atoi(map_row[j]);
		if (gl->map[i][j] == 0)
			gl->pos = (t_2dpt){i, j};
	}
}

void	parse_obj_data(t_gl *gl, char *data)
{
	char	**object_string_data_total;
	int		i;
	int		width;

	gl->stored_width = 0;
	object_string_data_total = ft_strsplit(data, '\n');
	gl->map_height = get_double_char_size(object_string_data_total);
	gl->map = (int**)ft_memalloc(sizeof(int*) * (gl->map_height + 1));
	i = 0;
	while (object_string_data_total[i])
	{
		get_the_data(gl, object_string_data_total[i], &width, i);
		i++;
	}
	if (gl->pos[0] == -1 || gl->pos[1] == -1)
		errorify("Yo, at least give me a place to put you...sigh...");
	free_array((void **)object_string_data_total);
	free(data);
}
