/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_and_music.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 01:17:56 by besellem          #+#    #+#             */
/*   Updated: 2021/02/15 11:15:26 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define GAME_SOUND_PATH "./sounds/top_gun.wav"
#define GAME_SOUND_DURATION 8

/*
** time() function used here to determine when the music has finished to
** replay it
*/

void	play_global_music(t_cub *cub)
{
	time_t now;

	now = time(NULL);
	if (cub->sound_time == 0 || now - cub->sound_time >= GAME_SOUND_DURATION)
	{
		system(SOUND_CMD" "GAME_SOUND_PATH" 2>/dev/null&");
		cub->sound_time = now;
	}
}
