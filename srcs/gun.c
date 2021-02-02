/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:23:51 by besellem          #+#    #+#             */
/*   Updated: 2021/02/02 20:12:19 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Display gun only when the window is large enough for it and when the gun's
** texture heigh is inferior to the window's heigh divided by 2 (center)
*/

void	display_gun(t_cub *cub)
{
	t_uint32	color;
	int			i;
	int			j;

	if (cub->txtr_gun.x >= cub->win_w || cub->txtr_gun.y >= cub->win_h / 2)
		return ;
	i = -1;
	while (++i < cub->txtr_gun.x)
	{
		j = -1;
		while (++j < cub->txtr_gun.y)
		{
			color = *(t_uint32 *)(cub->txtr_gun.addr + \
				(cub->txtr_gun.size_line * j) + \
				(i * (cub->txtr_gun.bits_per_pixel / 8)));
			if (color != 0U)
			{
				ft_pixel_put(cub, ((cub->win_w - cub->txtr_gun.x) / 2) + i,
					cub->win_h - cub->txtr_gun.y + j, color);
			}
		}
	}
}
