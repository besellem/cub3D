/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_sp_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:01:57 by besellem          #+#    #+#             */
/*   Updated: 2021/03/02 14:23:59 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sp_cast	*get_sprite_pos(t_cub *cub)
{
	t_sp_cast	*sp_cast;
	int			count;
	int			x;
	int			y;

	if (!(sp_cast = sprite_cast_init(cub)))
		return (NULL);
	count = 0;
	y = -1;
	while (++y < cub->map_size_y)
	{
		x = -1;
		while (++x < cub->map_size_x)
		{
			if (cub->map[y][x] == '2')
			{
				cub->sprites[count].x = x;
				cub->sprites[count].y = y;
				++count;
			}
		}
	}
	return (sp_cast);
}

void		pixel_put_sprite(t_cub *cub, t_sp_cast *sp_cast)
{
	sp_cast->tex_y = ((sp_cast->y - cub->win_h / 2
						+ sp_cast->sprite_height / 2)
						* cub->txtrs[4].y) / sp_cast->sprite_height;
	ft_memcpy(&sp_cast->color, cub->txtrs[4].addr + sp_cast->tex_y
			* cub->txtrs[4].size_line + sp_cast->tex_x * cub->txtrs[4].bpp / 8,
			sizeof(uint32_t));
}

void		paint_pixel(t_cub *cub, t_sp_cast *sp_cast)
{
	ft_memcpy(cub->img.addr + sp_cast->y * cub->img.size_line
			+ sp_cast->stripe * cub->img.bpp / 8, cub->txtrs[4].addr
			+ sp_cast->tex_y * cub->txtrs[4].size_line + sp_cast->tex_x
			* cub->txtrs[4].bpp / 8, sizeof(uint32_t));
}
