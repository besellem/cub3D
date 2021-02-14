/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:53:06 by besellem          #+#    #+#             */
/*   Updated: 2021/02/14 16:07:38 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** GET THE DISTANCE BETWEEN 2 POINTS (PYTHAGORE)
*/

double		get_dist(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

/*
** GET THE INTEGRAL PART OF A DECIMAL NUMBER
** ex: 12.44 -> 12.00
*/

double		get_dec(double n)
{
	return (n - (int)n);
}

/*
** DO NB1 - NB2 WITHOUT BEING < 0. IF THIS IS THE CASE, RETURN 0
** (mainly used in the raycasting calculations - prevents segv)
*/

int			safe_min(int nb1, int nb2)
{
	if (nb1 - nb2 < 0)
		return (0);
	return (nb1 - nb2);
}

/*
** Check if a line is rgb without any other character than spaces or digits at
** the right places
**
** ex:
** "  0234   " -> 1
** "    0234s" -> 0
** "0"         -> 1
*/

int			check_rgb(char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] == ' ')
		++i;
	while (s[i] && ft_isdigit(s[i]))
		++i;
	while (s[i] && s[i] == ' ')
		++i;
	if (s[i])
		return (0);
	return (1);
}

uint32_t	ft_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r | (g << 8) | (b << 16) | (a << 24));
}
