/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 15:01:33 by besellem          #+#    #+#             */
/*   Updated: 2021/02/02 22:56:38 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void		init_bonus(t_cub *cub)
{
	if (BONUS)
	{
		init_gun(cub);
		set_cub_size(cub);
		cub->life = 100;
	}
}
