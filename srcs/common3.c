/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 01:46:24 by besellem          #+#    #+#             */
/*   Updated: 2020/12/22 19:34:03 by besellem         ###   ########.fr       */
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
	double normed;

	normed = ft_deg2rad((int)ft_rad2deg(angle) % 360);
	if (normed < 0)
		return (normed + 2 * M_PI);
	return (normed);
}
