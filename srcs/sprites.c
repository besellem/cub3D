/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 10:28:26 by besellem          #+#    #+#             */
/*   Updated: 2021/01/25 12:48:14 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** REINITIALIZE EACH SPRITE'S STRUCT (EXCEPT ITS COORDINATES)
** The use of memset is useful here in case of modifications on t_sprite struct
*/

void	init_sprites_hit(t_cub *cub)
{
	int i;
	int tmp_x;
	int tmp_y;

	i = -1;
	while (++i < cub->sp_ocs - 1)
	{
		tmp_x = cub->sprites[i].x;
		tmp_y = cub->sprites[i].y;
		ft_memset(&cub->sprites[i], 0, sizeof(t_sprite));
		(&cub->sprites[i])->x = tmp_x;
		(&cub->sprites[i])->y = tmp_y;
	}
}

void	get_sprites(t_cub *cub)
{
	(void)cub;
}
