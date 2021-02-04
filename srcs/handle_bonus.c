/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 15:01:33 by besellem          #+#    #+#             */
/*   Updated: 2021/02/04 21:36:53 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define GAME_SOUND_PATH "./sounds/top_gun.wav"
#define GAME_SOUND_DURATION 8

/*
** These functions are only called when BONUS macro is defined
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

static void	init_gun(t_cub *cub)
{
	int fd;

	if ((fd = open(GUN_PATH, O_RDONLY)) == -1 || close(fd))
		ft_error("Unable to open a texture", cub, __FILE__, __LINE__);
	fill_texture(cub, &cub->txtr_gun, GUN_PATH);
}

void		play_music(t_cub *cub)
{
	time_t now;

	now = time(NULL);
	if (cub->sound_time == 0 || now - cub->sound_time >= GAME_SOUND_DURATION)
	{
		// system(SOUND_CMD" "GAME_SOUND_PATH" 2>/dev/null&");
		cub->sound_time = now;
	}
}

void		init_bonus(t_cub *cub)
{
	if (BONUS)
	{
		init_gun(cub);
		set_cub_size(cub);
		cub->life = 100;
	}
}
