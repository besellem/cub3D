/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 21:31:15 by besellem          #+#    #+#             */
/*   Updated: 2021/01/05 12:13:32 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_texture(t_cub *cub, t_img *txtre, char *path)
{
	if (file_got_ext(path, ".xpm"))
	{
		if (!(txtre->ptr = mlx_xpm_file_to_image(cub->mlx, path, &(txtre->x),
											&(txtre->y))))
			ft_error("Unable to open a texture", cub, __FILE__, __LINE__);
	}
	else
		ft_error("Not a valid texture file", cub, __FILE__, __LINE__);
	txtre->addr = mlx_get_data_addr(txtre->ptr, &(txtre->bits_per_pixel),
									&(txtre->size_line), &(txtre->endian));
}

void		load_textures(t_cub *cub)
{
	int i;

	if (!(cub->txtrs = (t_img *)malloc(sizeof(t_img) * TEXTURES_COUNT)))
		ft_error("Malloc error", cub, __FILE__, __LINE__);
	i = -1;
	while (++i < TEXTURES_COUNT)
	{
		(&(cub->txtrs[i]))->ptr = NULL;
		(&(cub->txtrs[i]))->addr = NULL;
	}
	fill_texture(cub, &(cub->txtrs[0]), cub->txtr_no);
	fill_texture(cub, &(cub->txtrs[1]), cub->txtr_so);
	fill_texture(cub, &(cub->txtrs[2]), cub->txtr_ea);
	fill_texture(cub, &(cub->txtrs[3]), cub->txtr_we);
	fill_texture(cub, &(cub->txtrs[4]), cub->txtr_s);
}

int			are_specs_complete(t_cub *cub)
{
	return (cub->grnd_color != -1 &&
		cub->sky_color != -1 &&
		cub->win_h != -1 &&
		cub->win_w != -1 &&
		cub->txtr_no &&
		cub->txtr_so &&
		cub->txtr_ea &&
		cub->txtr_we &&
		cub->txtr_s);
}

void		cub_parser(char *file, t_cub *cub)
{
	int fd;

	if ((fd = open(file, O_RDONLY)) == -1 ||
		ft_strcmp(file + (ft_strlen(file) - 4), ".cub") != 0)
	{
		ft_putendl_fd(CUB_ERR, 2);
		perror(file);
		exit(EXIT_FAILURE);
	}
	cub_fill_specs(fd, cub);
	parse_map(fd, cub);
	close(fd);
	check_map(cub);
}
