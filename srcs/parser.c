/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 21:31:15 by besellem          #+#    #+#             */
/*   Updated: 2021/01/18 16:01:31 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_texture(t_cub *cub, t_img *tx, char *path)
{
	if (file_got_ext(path, ".xpm"))
	{
		tx->ptr = mlx_xpm_file_to_image(cub->mlx, path, &tx->x, &tx->y);
		if (!tx->ptr)
			ft_error("Unable to open a texture", cub, __FILE__, __LINE__);
	}
	else
		ft_error("Not a valid texture file", cub, __FILE__, __LINE__);
	tx->addr = mlx_get_data_addr(tx->ptr, &tx->bits_per_pixel, &tx->size_line,
								&tx->endian);
	if (!tx->addr)
		ft_error("Malloc error", cub, __FILE__, __LINE__);
}

static void	load_textures(t_cub *cub)
{
	int i;

	if (!(cub->txtrs = (t_img *)malloc(sizeof(t_img) * TEXTURES_COUNT)))
		ft_error("Malloc error", cub, __FILE__, __LINE__);
	i = -1;
	while (++i < TEXTURES_COUNT)
		ft_memset(&cub->txtrs[i], 0, sizeof(t_img));
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

int			check_around(char **map, size_t x, size_t y)
{
	if (map[y][x - 1] && map[y][x + 1] && (map[y][x - 1] == ' ' ||
		map[y][x + 1] == ' '))
		return (0);
	if (map[y - 1][x] && map[y + 1][x] && (map[y - 1][x] == ' ' ||
		map[y + 1][x] == ' '))
		return (0);
	return (1);
}

int			check_line(t_cub *cub, char *line, size_t y)
{
	size_t i;

	i = 0;
	while (line[i] && line[i] == ' ')
		ft_putchar(line[i++]);
	if (line[i] == '0')
		return (i);
	while (line[i])
	{
		if ((line[i] == '2' || line[i] == '0') && !check_around(cub->map, i, y))
			return (i);
		// if (line[i] == ' ' && !check_space())
		// 	return (i);
		if (line[i] == '0')
		{
			while (line[i] && line[i] == '0')
				ft_putchar(line[i++]);
			if (!line[i] || line[i] == ' ')
				return (i);
		}
		ft_putchar(line[i++]);
	}
	return (-1);
}

int			validate_map(t_cub *cub)
{
	size_t	y;
	int		check;

	y = 0;
	while (cub->map[y] != NULL)
	{
		if ((check = check_line(cub, cub->map[y], y)) != -1)
		{
			ft_printf(B_RED"%c\n"CLR_COLOR, cub->map[y][check]);
			ft_printf("[%d;%d]\n", check + 1, y + 1);
			return (0);
		}
		ft_putendl("");
		++y;
	}
	return (1);
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
	if (!validate_map(cub))
		ft_error("Invalid Map", cub, __FILE__, __LINE__);
	
	// TO REMOVE
	print_specs(cub);
	ft_free_cub(cub);
	printf(B_BLUE"-> ALL GOOD\n"CLR_COLOR);
	exit(EXIT_SUCCESS);
}
