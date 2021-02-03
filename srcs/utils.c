/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 02:08:15 by besellem          #+#    #+#             */
/*   Updated: 2021/02/03 13:56:24 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(t_cub *cub)
{
	size_t x;
	size_t y;

	y = 0;
	while (y < cub->map_size_y)
	{
		x = 0;
		while (x < cub->map_size_x)
		{
			if (x == (size_t)cub->pos_x && y == (size_t)cub->pos_y)
				ft_printf(B_GREEN"%c"CLR_COLOR, cub->map[y][x]);
			else
				ft_putchar(cub->map[y][x]);
			++x;
		}
		write(1, "\n", 1);
		++y;
	}
}

void	print_specs(t_cub *cub)
{
	ft_putendl("-- Specs --");
	ft_putendl("{");
	ft_printf("    cub->mlx:        %p\n", cub->mlx);
	ft_printf("    cub->win:        %p\n", cub->win);
	ft_printf("    cub->win_w:      %d -> %d\n", cub->parsed_w, cub->win_w);
	ft_printf("    cub->win_h:      %d -> %d\n", cub->parsed_h, cub->win_h);
	ft_printf("    cub->sky_color:  %#x\n", cub->sky_color);
	ft_printf("    cub->grnd_color: %#x\n", cub->grnd_color);
	ft_printf("    cub->txtr_no:    [%p] %s\n", cub->txtr_no, cub->txtr_no);
	ft_printf("    cub->txtr_so:    [%p] %s\n", cub->txtr_so, cub->txtr_so);
	ft_printf("    cub->txtr_ea:    [%p] %s\n", cub->txtr_ea, cub->txtr_ea);
	ft_printf("    cub->txtr_we:    [%p] %s\n", cub->txtr_we, cub->txtr_we);
	ft_printf("    cub->txtr_s:     [%p] %s\n", cub->txtr_s, cub->txtr_s);
	ft_printf("    cub->map_size_x: %lld\n", cub->map_size_x);
	ft_printf("    cub->map_size_y: %lld\n", cub->map_size_y);
	ft_printf("    cub->drxion:     %f\n", cub->drxion);
	ft_printf("    cub->pos_x:      %f\n", cub->pos_x);
	ft_printf("    cub->pos_y:      %f\n", cub->pos_y);
	ft_printf("    cub->increment:  %f\n", cub->increment);
	ft_printf("    cub->cub_size:   %d\n", cub->cub_size);
	ft_putendl("}\n");
	print_map(cub);
	ft_putendl("\n----\n");
}

void	sprites_dump(t_cub *cub)
{
	int i;

	if (cub->sp_ocs <= 0)
		return ;
	ft_putendl("-- Sprites Dump --");
	ft_putendl("{");
	i = -1;
	while (++i < cub->sp_ocs)
	{
		ft_printf("    cub->sprites[%2d] => dist[%.3] x[%2d] y[%2d]\n",
			i, cub->sprites[i].distance, cub->sprites[i].x, cub->sprites[i].y);
	}
	ft_putendl("}\n");
}
