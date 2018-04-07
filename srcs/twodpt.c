/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twodpt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 10:40:40 by mray              #+#    #+#             */
/*   Updated: 2018/03/31 10:40:40 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

double	dot(t_2dpt pt1, t_2dpt pt2)
{
	t_2dpt product;

	product = pt1 * pt2;
	return (product[0] + product[1]);
}

double	mag(t_2dpt pt)
{
	t_2dpt squares;

	squares = pt * pt;
	return (sqrt(squares[0] + squares[1]));
}

double	angle_between(t_2dpt one, t_2dpt two)
{
	return (acos(dot(one, two) / (mag(one) * mag(two))));
}
