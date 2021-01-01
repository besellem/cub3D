/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 01:46:24 by besellem          #+#    #+#             */
/*   Updated: 2020/12/31 16:11:54 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_rgb(int color)
{
	return (color >= 0 && color <= 255);
}

long	ft_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return ((long)(((r << 8) + g) << 8) + b);
}

double	ft_deg2rad(int deg)
{
	return (deg * (M_PI / 180));
}

double	ft_rad2deg(double rad)
{
	return (rad * (180 / M_PI));
}

double	ft_norm_angle(double angle)
{
	double fract;
	double integral;

	fract = modf(angle, &integral);
	fract += ((int)integral % 360);
	if (fract < 0)
		fract += M_2PI;
	else if (fract >= M_2PI)
		fract -= M_2PI;
	return (fract);
}
