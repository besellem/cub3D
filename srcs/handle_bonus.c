/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 15:01:33 by besellem          #+#    #+#             */
/*   Updated: 2021/02/09 11:17:52 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define GAME_SOUND_PATH "./sounds/top_gun.wav"
#define GAME_SOUND_DURATION 8

/*
** THESE FUNCTIONS ARE ONLY CALLED WHEN `BONUS' MACRO IS DEFINED
*/

/*
** Set each minimap's cub size in pixels. It will always be maximum 1/3 of the
** screen size
*/

static void	set_cub_size(t_cub *cub)
{
	int max_w;
	int max_h;

	max_w = (double)(cub->win_w / 3) / cub->map_size_x;
	max_h = (double)(cub->win_h / 3) / cub->map_size_y;
	if (max_w > max_h)
		cub->cub_size = max_h;
	else
		cub->cub_size = max_w;
}

static void	init_gun(t_cub *cub, int count)
{
	const char	*gun_txtr[GUN_GIF_NB] = {
		"./assets/gun/gun_status_1.xpm",
		"./assets/gun/gun_status_2.xpm",
		"./assets/gun/gun_status_3.xpm",
		"./assets/gun/gun_status_4.xpm",
		"./assets/gun/gun_status_5.xpm"
	};
	const int	fd = open(gun_txtr[count], O_RDONLY);

	if (fd == -1 || close(fd))
		ft_error("Unable to open a texture", cub, __FILE__, __LINE__);
	fill_texture(cub, &cub->txtr_gun[count], (char *)gun_txtr[count]);
	if (count != 0)
		init_gun(cub, count - 1);
}

void		init_bonus(t_cub *cub)
{
	if (BONUS)
	{
		init_gun(cub, GUN_GIF_NB - 1);
		set_cub_size(cub);
		cub->life = 100;
	}
}
