/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_sp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:01:40 by besellem          #+#    #+#             */
/*   Updated: 2021/03/02 14:27:06 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprite(t_cub *cub, t_sp_cast *sp_cast)
{
	t_sprite	tmp;
	double		sprite_dist[2];
	int			count;

	count = 0;
	while (count + 1 < cub->sprites_ocs)
	{
		sprite_dist[0] = ((cub->pos_x - cub->sprites[count].x)
				* (cub->pos_x - cub->sprites[count].x)
				+ (cub->pos_y - cub->sprites[count].y)
				* (cub->pos_y - cub->sprites[count].y));
		sprite_dist[1] = ((cub->pos_x - cub->sprites[count + 1].x)
				* (cub->pos_x - cub->sprites[count + 1].x)
				+ (cub->pos_y - cub->sprites[count + 1].y)
				* (cub->pos_y - cub->sprites[count + 1].y));
		if (sprite_dist[0] < sprite_dist[1])
		{
			tmp = cub->sprites[count];
			cub->sprites[count] = cub->sprites[count + 1];
			cub->sprites[count + 1] = tmp;
			count = 0;
		}
		else
			++count;
	}
}

void	sprite_projection(t_cub *cub, t_sp_cast *sp_cast, int i)
{
	sp_cast->sprite_x = cub->sprites[i].x - (cub->pos_x - 0.5);
	sp_cast->sprite_y = cub->sprites[i].y - (cub->pos_y - 0.5);
	sp_cast->inv_det = 1.0 / (cub->camera->plane_x * cub->camera->dir_y
			- cub->camera->dir_x * cub->camera->plane_y);
	sp_cast->transform_x = sp_cast->inv_det * (cub->camera->dir_y
			* sp_cast->sprite_x - cub->camera->dir_x
			* sp_cast->sprite_y);
	sp_cast->transform_y = sp_cast->inv_det * (-cub->camera->plane_y
			* sp_cast->sprite_x + cub->camera->plane_x
			* sp_cast->sprite_y);
	sp_cast->sprite_screen_x = (int)((cub->win_w / 2) *
			(1 + sp_cast->transform_x / sp_cast->transform_y));
}

void	sprite_draw(t_cub *cub, t_sp_cast *sp_cast, t_ray_cast *ray)
{
	sp_cast->sprite_height = abs((int)(cub->win_h / (sp_cast->transform_y)));
	sp_cast->draw_start_y = -sp_cast->sprite_height / 2
							+ cub->win_h / 2 * cub->camera->cam_height;
	if (sp_cast->draw_start_y < 0)
		sp_cast->draw_start_y = 0;
	sp_cast->draw_end_y = sp_cast->sprite_height / 2
							+ cub->win_h / 2 * cub->camera->cam_height;
	if (sp_cast->draw_end_y >= cub->win_h)
		sp_cast->draw_end_y = cub->win_h - 1;
	sp_cast->sprite_width = abs((int)(cub->win_h / (sp_cast->transform_y)));
	sp_cast->draw_start_x = -sp_cast->sprite_width
												/ 2 + sp_cast->sprite_screen_x;
	if (sp_cast->draw_start_x < 0)
		sp_cast->draw_start_x = 0;
	sp_cast->draw_end_x = sp_cast->sprite_width / 2 + sp_cast->sprite_screen_x;
	if (sp_cast->draw_end_x >= cub->win_w)
		sp_cast->draw_end_x = cub->win_w - 1;
	sp_cast->stripe = sp_cast->draw_start_x;
	sprite_dracubg(cub, sp_cast, ray);
}

void	sprite_dracubg(t_cub *cub, t_sp_cast *sp_cast, t_ray_cast *ray)
{
	while (sp_cast->stripe < sp_cast->draw_end_x)
	{
		sp_cast->tex_x = (int)((sp_cast->stripe
						- (-sp_cast->sprite_width / 2
						+ sp_cast->sprite_screen_x))
						* cub->sprite->width / sp_cast->sprite_width);
		if (sp_cast->transform_y > 0 && sp_cast->stripe > 0
				&& sp_cast->stripe < cub->win_w
				&& sp_cast->transform_y < ray->zbuffer[sp_cast->stripe])
		{
			sp_cast->y = sp_cast->draw_start_y;
			while (sp_cast->y < sp_cast->draw_end_y)
			{
				pixel_put_sprite(cub, sp_cast);
				if ((sp_cast->color & 0x00FFFFFF) != 0)
					paint_pixel(cub, sp_cast);
				++sp_cast->y;
			}
		}
		++sp_cast->stripe;
	}
}

int		sprite_casting(t_cub *cub, t_ray_cast *ray)
{
	t_sp_cast	*sp_cast;
	int			i;

	if (!(sp_cast = get_sprite_pos(cub)))
		return (0);
	sort_sprite(cub, sp_cast);
	i = 0;
	while (i < cub->sprites_ocs)
	{
		sprite_projection(cub, sp_cast, i);
		sprite_draw(cub, sp_cast, ray);
		i++;
	}
	free(sp_cast->sprite);
	free(sp_cast);
	return (1);
}