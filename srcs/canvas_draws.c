/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_draws.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 16:56:06 by mray              #+#    #+#             */
/*   Updated: 2018/04/01 16:56:06 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void add_sun(t_canvas *canvas)
{
	int sun_width;
	int y;
	int x;
	int color;

	sun_width = 500;
	color = 0xFFA500;
	y = (HEIGHT / 2 - sun_width / 2) - 1;
	while (++y < HEIGHT / 2 + sun_width / 2)
	{
		x = (WIDTH / 2 - sun_width / 2) - 1;
		if ((y % 1) == 0)
			color -= 1;
		while (++x < WIDTH / 2 + sun_width / 2)
			store_pix(canvas, x, y, color);
	}
}
void reset_canvas(t_canvas *canvas)
{
	int x;
	int y;
	int color;

	y = -1;
	color = 0xFFA500;
	while (++y < HEIGHT / 2)
	{
		x = -1;
		if (y % 2 == 0)
			color -= 1;
		while (++x < WIDTH)
			store_pix(canvas, x, y, color);
	}
	add_sun(canvas);
	y--;
	color = 0x00BFFF;
	while (++y < HEIGHT)
	{
		x = -1;
		if ((y % 3) == 0)
			color += 1;
		// color = generate_random_hex() * 3;
		while (++x < WIDTH)
			store_pix(canvas, x, y, color);
	}
}

void put_game_over(t_gl *gl, t_canvas *canvas)
{
	reset_canvas(canvas);
	mlx_string_put(gl->lib, gl->surf, WIDTH / 2, HEIGHT / 2, 0xFFFFFF, "GAME OVER...  >+<");
}
