/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 10:28:26 by besellem          #+#    #+#             */
/*   Updated: 2021/01/31 11:56:36 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** REINITIALIZE EACH SPRITE'S STRUCT (EXCEPT ITS COORDINATES)
** The use of memset is useful here in case of modifications on t_sprite struct
*/

void	init_sprites_hit(t_cub *cub)
{
	int tmp_x;
	int tmp_y;
	int i;

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
