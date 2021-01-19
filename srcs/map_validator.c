/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:22:27 by besellem          #+#    #+#             */
/*   Updated: 2021/01/19 13:24:31 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_around(t_cub *cub, char **map, size_t x, size_t y)
{
	if (x - 1 >= 0 && x + 1 < cub->map_size_x &&
		y - 1 >= 0 && y + 1 < cub->map_size_y)
	{
		if (map[y][x - 1] && map[y][x + 1] && (map[y][x - 1] == ' ' ||
			map[y][x + 1] == ' '))
			return (0);
		if (map[y - 1][x] && map[y + 1][x] && (map[y - 1][x] == ' ' ||
			map[y + 1][x] == ' '))
			return (0);
	}
	else
		return (0);
	return (1);
}

static int	check_space(t_cub *cub, char **map, size_t x, size_t y)
{
	if (((int)x - 1 >= 0 && map[y][x - 1] != ' ' && map[y][x - 1] != '1') ||
		(x + 1 < cub->map_size_x && map[y][x + 1] != ' ' &&
		map[y][x + 1] != '1'))
	{
		return (0);
	}
	if (((int)y - 1 >= 0 && map[y - 1][x] != ' ' && map[y - 1][x] != '1') ||
		(y + 1 < cub->map_size_y && map[y + 1][x] != ' ' &&
		map[y + 1][x] != '1'))
	{
		return (0);
	}
	return (1);
}

static int	check_line(t_cub *cub, char *line, size_t y)
{
	size_t i;

	i = 0;
	while (line[i] && line[i] == ' ')
		ft_putchar(line[i++]);
	if (line[i] == '0')
		return (i);
	while (line[i])
	{
		if ((line[i] == '2' || line[i] == '0') &&
			!check_around(cub, cub->map, i, y))
			return (i);
		else if (line[i] == ' ' && !check_space(cub, cub->map, i, y))
			return (i);
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

int			map_validator(t_cub *cub)
{
	size_t	y;
	int		check;

	y = 0;
	while (cub->map[y] != NULL)
	{
		if ((check = check_line(cub, cub->map[y], y)) != -1)
		{
			ft_printf(B_RED"%c\n"CLR_COLOR, cub->map[y][check]);
			ft_printf(B_GREEN"%*.d^ error here "CLR_COLOR, check, 0);
			ft_printf("[%d;%d]\n", check + 1, y + 1);
			return (0);
		}
		ft_putendl("");
		++y;
	}
	return (1);
}