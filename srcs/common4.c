/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:53:06 by besellem          #+#    #+#             */
/*   Updated: 2021/01/13 15:18:21 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** GET THE DISTANCE BETWEEN 2 POINTS (PYTHAGORE)
*/

double	get_dist(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

/*
** GET THE INTEGRAL PART OF A DECIMAL NUMBER
*/

double	get_dec(double n)
{
	return (n - (int)n);
}

/*
** DO NB1 - NB2 WITHOUT BEING < 0. IF THIS IS THE CASE, RETURN 0
** (mainly used in the raycasting calculations - prevents segaulting)
*/

int		safe_min(int nb1, int nb2)
{
	if (nb1 - nb2 < 0)
		return (0);
	return (nb1 - nb2);
}
