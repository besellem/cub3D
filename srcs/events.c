/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:02:16 by besellem          #+#    #+#             */
/*   Updated: 2021/01/19 13:27:19 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_player(t_cub *cub)
{
	double step;

	if (cub->turn != 0)
		cub->drxion = ft_norm_angle(cub->drxion + cub->turn * ft_deg2rad(4));
	if (cub->dh != 0)
	{
		step = cub->pos_x + cos(cub->drxion) * cub->dh * cub->increment;
		if (cub->map[(int)cub->pos_y][(int)step] == '0')
			cub->pos_x = step;
		step = cub->pos_y + sin(cub->drxion) * cub->dh * cub->increment;
		if (cub->map[(int)step][(int)cub->pos_x] == '0')
			cub->pos_y = step;
	}
	if (cub->dw != 0)
	{
		step = cub->pos_x + cub->dw * (sin(-cub->drxion) * cub->increment);
		if (cub->map[(int)cub->pos_y][(int)step] == '0')
			cub->pos_x = step;
		step = cub->pos_y + cub->dw * (cos(-cub->drxion) * cub->increment);
		if (cub->map[(int)step][(int)cub->pos_x] == '0')
			cub->pos_y = step;
	}
}

static int	need_update(t_cub *cub)
{
	return (cub->dh != 0 || cub->dw != 0 || cub->turn != 0);
}

void		update_view(t_cub *cub)
{
	move_player(cub);
	cast_all_rays(cub);
	update_cubs(cub);
	// update_minimap(cub);
}

int			ft_refresh(t_cub *cub)
{
	if (need_update(cub))
	{
		update_view(cub);
		mlx_put_image_to_window(cub->mlx, cub->win, cub->img->ptr, 0, 0);
		return (0);
	}
	return (1);
}
