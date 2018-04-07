/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 13:57:35 by mray              #+#    #+#             */
/*   Updated: 2018/02/26 13:57:35 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		expose_handler(t_params *para)
{
	t_gl		*gl;
	t_canvas	*canvas;

	gl = para->p1;
	canvas = para->p2;
	mlx_clear_window(gl->lib, gl->surf);
	mlx_put_image_to_window(gl->lib, gl->surf, canvas->img, 0, 0);
	return (0);
}

int exit_handler(t_params *para)
{
	t_gl		*gl;
	t_canvas	*canvas;

	gl = para->p1;
	canvas = para->p2;
	exit(0);
}

int		main(int argc, char **argv)
{
	t_gl		*gl;
	void		*mlx;
	void		*window;
	t_canvas	*canvas;
	t_params	*para;

	if (argc == 2 || argc == 3)
	{
		para = (t_params *)malloc(sizeof(t_params));
		mlx = mlx_init();
		window = mlx_new_window(mlx, WIDTH, HEIGHT, "Wolfenstein 3D");
		gl = create_gl(mlx, window);
		canvas = create_canvas(gl);
		para->p1 = gl;
		para->p2 = canvas;
		if (argc == 3 && ft_atoi(argv[2]) == 4)
			gl->d4 = -1.0;
		parse_obj_data(gl, read_in(argv[1]));
		scenify(gl, canvas);
		mlx_hook(gl->surf, 2, 0, key_handler, para);
		mlx_hook(gl->surf, 17, 0, exit_handler, para);
		mlx_expose_hook(gl->surf, expose_handler, para);
		mlx_loop(gl->lib);
	}
}
