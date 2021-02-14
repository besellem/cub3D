/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 02:08:15 by besellem          #+#    #+#             */
/*   Updated: 2021/02/14 19:12:57 by besellem         ###   ########.fr       */
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
	printf("-- Specs --\n");
	printf("{\n");
	printf("    cub->mlx:        %p\n", cub->mlx);
	printf("    cub->win:        %p\n", cub->win);
	printf("    cub->win_w:      %d -> %d\n", cub->parsed_w, cub->win_w);
	printf("    cub->win_h:      %d -> %d\n", cub->parsed_h, cub->win_h);
	printf("    cub->sky_color:  %X\n", cub->sky_color);
	printf("    cub->grnd_color: %X\n", cub->grnd_color);
	printf("    cub->txtr_no:    %s\n", cub->txtr_no);
	printf("    cub->txtr_so:    %s\n", cub->txtr_so);
	printf("    cub->txtr_ea:    %s\n", cub->txtr_ea);
	printf("    cub->txtr_we:    %s\n", cub->txtr_we);
	printf("    cub->txtr_s:     %s\n", cub->txtr_s);
	printf("    cub->map_size_x: %zu\n", cub->map_size_x);
	printf("    cub->map_size_y: %zu\n", cub->map_size_y);
	printf("    cub->drxion:     %f\n", cub->drxion);
	printf("    cub->pos_x:      %f\n", cub->pos_x);
	printf("    cub->pos_y:      %f\n", cub->pos_y);
	printf("    cub->increment:  %.2f\n", cub->increment);
	printf("    cub->cub_size:   %dpx\n", cub->cub_size);
	printf("}\n\n");
	print_map(cub);
	printf("\n----\n\n");
}

void	sprites_dump(t_cub *cub)
{
	int i;

	if (cub->sprites_ocs <= 0)
		return ;
	printf("-- Sprites Dump (%d) --\n", cub->sprites_ocs);
	printf("Position: x["B_RED"%.2f"CLR_COLOR"] y["B_RED"%.2f"CLR_COLOR"]\n",
		cub->pos_x, cub->pos_y);
	printf("{\n");
	i = -1;
	while (++i < cub->sprites_ocs)
	{
		printf("    cub->sprites[%2d] => ", i);
		printf("x["B_GREEN"%2d"CLR_COLOR"] ", cub->sprites[i].x);
		printf("y["B_GREEN"%2d"CLR_COLOR"] ", cub->sprites[i].y);
		if (cub->sprites[i].hit == 1)
			printf("hit["B_RED"%d"CLR_COLOR"] ", cub->sprites[i].hit);
		else
			printf("hit["B_GREEN"%d"CLR_COLOR"] ", cub->sprites[i].hit);
		printf("dist["B_GREEN"%.3f"CLR_COLOR"]\n", cub->sprites[i].distance);
	}
	printf("}\n\n");
}
