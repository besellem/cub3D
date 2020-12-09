/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 21:31:15 by besellem          #+#    #+#             */
/*   Updated: 2020/12/10 00:57:35 by besellem         ###   ########.fr       */
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

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		perror("Unable to open the file\n");
		exit(EXIT_FAILURE);
	}
	cub_fill_specs(fd, specs);
}
