/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 21:31:15 by besellem          #+#    #+#             */
/*   Updated: 2021/01/17 20:05:21 by besellem         ###   ########.fr       */
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

static void	load_textures(t_cub *cub)
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

void		cub_parser(int ac, char **av, t_cub *cub)
{
	int fd;

	if (ac == 3 && ft_strcmp(av[2], "--save") == 0)
		cub->save_opt = 1;
	else if (ac == 3)
		ft_error("Argument error", cub, __FILE__, __LINE__);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		ft_error("Unable to start mlx", cub, __FILE__, __LINE__);
	if ((fd = open(av[1], O_RDONLY)) == -1 ||
		ft_strcmp(av[1] + (ft_strlen(av[1]) - 4), ".cub") != 0)
	{
		ft_putendl_fd(CUB_ERR, 2);
		perror(av[1]);
		exit(EXIT_FAILURE);
	}
	cub_fill_specs(fd, cub);
	load_textures(cub);
	parse_map(fd, cub);
	close(fd);
	check_map(cub);
	
	// TO REMOVE
	// print_specs(cub);
	// ft_free_cub(cub);
	// printf(B_BLUE"-> ALL GOOD\n"CLR_COLOR);
	// exit(EXIT_SUCCESS);
}
