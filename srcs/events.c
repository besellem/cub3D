/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:02:16 by besellem          #+#    #+#             */
/*   Updated: 2020/12/16 00:53:51 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_quit(t_cub *cub)
{
	ft_putendl(B_RED"[Quit]"CLR_COLOR);
	mlx_destroy_window(cub->mlx, cub->win);
	free(cub->keys);
	free(cub->mlx);
	if (cub->map)
		ft_free_strs(cub->map);
	exit(EXIT_SUCCESS);
}

void	ft_key_left(t_cub *cub)
{
	ft_putendl("=> Move camera left <=");
	(void)cub;
}

void	ft_key_right(t_cub *cub)
{
	ft_putendl("=> Move camera right <=");
	(void)cub;
}

void	ft_move_front(t_cub *cub)
{
	cub->pos_y += cub->increment;
}

void	ft_move_back(t_cub *cub)
{
	cub->pos_y -= cub->increment;
}

void	ft_move_left(t_cub *cub)
{
	cub->pos_x -= cub->increment;
}

void	ft_move_right(t_cub *cub)
{
	cub->pos_x += cub->increment;
}

void	update_view(t_cub *cub)
{
	int x;
	int y;

	x = (int)cub->pos_x;
	y = (int)cub->pos_y;
	ft_printf("[ %f ; %f ]\n", cub->pos_x, cub->pos_y);
	mlx_pixel_put(cub->mlx, cub->win, x, y, 0xFFFFFF);
}

int		handle_key_event(int key, t_cub *cub)
{
	int i;

	i = -1;
	while (cub->keys[++i].f != NULL)
	{
		if (cub->keys[i].key == key)
		{
			ft_printf("key: [%d] f: [%p]\n", cub->keys[i].key, cub->keys[i].f);
			cub->keys[i].f(cub);
			update_view(cub);
			break ;
		}
	}
	return (0);
}
