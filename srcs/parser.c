/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 21:31:15 by besellem          #+#    #+#             */
/*   Updated: 2020/12/14 10:29:52 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		are_specs_complete(t_specs *specs)
{
	if (specs->color_ground != -1 && specs->color_sky != -1 &&
		specs->res_heigh != -1 && specs->res_width != -1 &&
		specs->texture_north && specs->texture_south && specs->texture_east &&
		specs->texture_west && specs->texture_sprite)
		return (1);
	return (0);
}

void	cub_parser(char *file, t_specs *specs)
{
	int fd;

	if ((fd = open(file, O_RDONLY)) == -1 ||
		ft_strcmp(file + (ft_strlen(file) - 4), ".cub") != 0)
	{
		ft_putendl_fd(CUB_ERR, 2);
		perror(file);
		exit(EXIT_FAILURE);
	}
	cub_fill_specs(fd, specs);
}
