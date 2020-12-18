/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 02:08:15 by besellem          #+#    #+#             */
/*   Updated: 2020/12/18 01:46:47 by besellem         ###   ########.fr       */
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
			ft_putchar(cub->map[y][x++]);
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
	ft_printf("    cub->win_w:      %d\n", cub->win_w);
	ft_printf("    cub->win_h:      %d\n", cub->win_h);
	ft_printf("    cub->sky_color:  0b%.32b\n", cub->sky_color);
	ft_printf("    cub->grnd_color: 0b%.32b\n", cub->grnd_color);
	ft_printf("    cub->txtr_no:    %s\n", cub->txtr_no);
	ft_printf("    cub->txtr_so:    %s\n", cub->txtr_so);
	ft_printf("    cub->txtr_ea:    %s\n", cub->txtr_ea);
	ft_printf("    cub->txtr_we:    %s\n", cub->txtr_we);
	ft_printf("    cub->txtr_s:     %s\n", cub->txtr_s);
	ft_printf("    cub->map_size_x: %lld\n", cub->map_size_x);
	ft_printf("    cub->map_size_y: %lld\n", cub->map_size_y);
	ft_printf("    cub->drxion:     %f\n", cub->drxion);
	ft_printf("    cub->pos_x:      %f\n", cub->pos_x);
	ft_printf("    cub->pos_y:      %f\n", cub->pos_y);
	ft_printf("    cub->increment:  %f\n", cub->increment);
	ft_putendl("}");
	print_map(cub);
	ft_putendl("----\n");
}

void	ft_get_env(void)
{
	if (KEY_ESC != -1)
		ft_putendl(B_GREEN"[macOS environnement]"CLR_COLOR);
	else
		ft_putendl(B_GREEN"[Linux (default) environnement]"CLR_COLOR);
}
