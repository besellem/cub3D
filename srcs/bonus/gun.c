/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:23:51 by besellem          #+#    #+#             */
/*   Updated: 2021/02/14 19:48:41 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define GUN_SHOT_SOUND_PATH "./sounds/gun_shot.wav"

/*
** Display gun only when the window is large enough for it and when the gun's
** texture heigh is inferior to the window's heigh divided by 2 (center)
*/

static void	set_gun_txtr_idx(t_cub *cub)
{
	if (cub->gun_status != 0)
	{
		if (cub->gun_status == -1)
		{
			cub->gun_status = 1;
			system(SOUND_CMD" "GUN_SHOT_SOUND_PATH" 2>/dev/null&");
		}
		else
			cub->gun_status++;
	}
	if (cub->gun_status > GUN_GIF_NB)
		cub->gun_status = 0;
}

static void	print_gun(t_cub *cub, t_img tx)
{
	uint32_t	clr;
	int			i;
	int			j;

	i = -1;
	while (++i < tx.x)
	{
		j = -1;
		while (++j < tx.y)
		{
			clr = *(uint32_t *)(tx.addr + j * tx.size_line + i * (tx.bpp / 8));
			if (clr != 0U)
				ft_pixel_put(cub, (cub->win_w - tx.x) / 2 + i,
							cub->win_h - tx.y + j, clr);
		}
	}
}

void		display_gun(t_cub *cub)
{
	int xmax;
	int ymax;
	int i;

	set_gun_txtr_idx(cub);
	xmax = 0;
	ymax = 0;
	i = -1;
	while (++i < GUN_GIF_NB)
	{
		if (xmax < cub->txtr_gun[i].x)
			xmax = cub->txtr_gun[i].x;
		if (ymax < cub->txtr_gun[i].y)
			ymax = cub->txtr_gun[i].y;
	}
	if (cub->win_w >= xmax && cub->win_h / 2 >= ymax)
	{
		print_gun(cub, cub->txtr_gun[cub->gun_status]);
		// mlx_put_image_to_window(cub->mlx,cub->win,
		// 	cub->txtr_gun[cub->gun_status].ptr,
		// 	((cub->win_w - cub->txtr_gun[cub->gun_status].x) / 2),
		// 	cub->win_h - cub->txtr_gun[cub->gun_status].y);
	}
}
