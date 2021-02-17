/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:53:06 by besellem          #+#    #+#             */
/*   Updated: 2021/02/17 12:54:46 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** GET THE DISTANCE BETWEEN 2 POINTS
*/

double	ft_pythagore(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

/*
** GET THE FRACTIONAL PART OF A DECIMAL NUMBER (keeping the sign)
** ex: -12.44 -> -0.44
*/

double	get_dec(double n)
{
	return (n - (int)n);
}

/*
** DO `NB1 - NB2` WITHOUT BEING < 0. IF THIS IS THE CASE, RETURN 0
** (mainly used in the raycasting calculations - prevents segv from the map)
*/

int		safe_min(int nb1, int nb2)
{
	if (nb1 - nb2 < 0)
		return (0);
	return (nb1 - nb2);
}