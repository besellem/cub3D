/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 23:39:13 by besellem          #+#    #+#             */
/*   Updated: 2021/01/08 13:12:10 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_img(t_cub *cub)
{
	cub->img = (t_img *)malloc(sizeof(t_img));
	if (!cub->img)
		return (1);
	ft_memset(cub->img, 0, sizeof(t_img));
	return (0);
}

static int	init_keys(t_cub *cub)
{
	cub->keys = (t_keys *)malloc(sizeof(t_keys));
	if (!cub->keys)
		return (1);
	ft_memset(cub->keys, 0, sizeof(t_keys));
	return (0);
}

/*
** cub->rays is malloc in the parser as we don't know win_w & win_h yet
*/

int			init_cub(t_cub *cub)
{
	ft_memset(cub, 0, sizeof(t_cub));
	if (init_img(cub))
		return (1);
	cub->win_w = -1;
	cub->win_h = -1;
	cub->sky_color = -1;
	cub->grnd_color = -1;
	cub->increment = 0.1;
	cub->cub_size = 8;
	if (init_keys(cub))
		return (1);
	return (0);
}
