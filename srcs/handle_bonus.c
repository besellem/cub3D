/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 15:01:33 by besellem          #+#    #+#             */
/*   Updated: 2021/01/24 15:08:17 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void		add_bonus(t_cub *cub)
{
	if (BONUS)
	{
		set_cub_size(cub);
	}
}
