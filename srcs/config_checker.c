/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 00:50:40 by besellem          #+#    #+#             */
/*   Updated: 2020/12/10 00:56:24 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	window_size_spec(char **split, t_specs *specs)
{
	if (ft_strs_size(split) != 3)
		ft_error("Bad resolution configuration\n");
	specs->res_width = ft_atol(split[1]);
	specs->res_heigh = ft_atol(split[2]);
	ft_free_strs(split);
	if (specs->res_width < 0 || specs->res_heigh < 0)
		ft_error("Bad resolution configuration\n");
}

/*
** The rgb variables are int type because we need to know if the rgb color
** from the config overflowed an unsigned char or not
*/

static void	color_specs(char where, char **split, t_specs *specs)
{
	long	color;
	int		r;
	int		g;
	int		b;

	if (ft_strs_size(split) != 3)
		ft_error("Bad color configuration\n");
	r = ft_atoi(split[0] + 2);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	ft_free_strs(split);
	if (!(is_rgb(r) && is_rgb(g) && is_rgb(b)))
		ft_error("Bad color configuration\n");
	color = ft_rgb(r, g, b);
	if (where == 'F' && specs->color_ground == -1)
		specs->color_ground = color;
	else if (where == 'C' && specs->color_sky == -1)
		specs->color_sky = color;
	else
		ft_error("Bad color configuration\n");
}

static void	texture_specs(char *line, t_specs *specs)
{
	char **nfos;

	nfos = ft_split(line, ' ');
	if (ft_strs_size(nfos) != 2)
		ft_error("Bad texture configuration\n");
	if (!*nfos || !nfos[1] || open(nfos[1], O_RDONLY) == -1)
		ft_error("Cannot open a texture file\n");
	if (!ft_strncmp(line, "NO ", 3) && !specs->texture_north)
		specs->texture_north = ft_strdup(nfos[1]);
	else if (!ft_strncmp(line, "SO ", 3) && !specs->texture_south)
		specs->texture_south = ft_strdup(nfos[1]);
	else if (!ft_strncmp(line, "WE ", 3) && !specs->texture_west)
		specs->texture_west = ft_strdup(nfos[1]);
	else if (!ft_strncmp(line, "EA ", 3) && !specs->texture_east)
		specs->texture_east = ft_strdup(nfos[1]);
	else if (!ft_strncmp(line, "S ", 2) && !specs->texture_sprite)
		specs->texture_sprite = ft_strdup(nfos[1]);
	else
	{
		ft_free_strs(nfos);
		ft_error("Doublons in texture configuration\n");
	}
	ft_free_strs(nfos);
}

static int	check_line(char *line, t_specs *specs, int *specs_completed)
{
	if (!ft_strncmp(line, "R ", 2))
		window_size_spec(ft_split(line, ' '), specs);
	else if (!ft_strncmp(line, "F ", 2))
		color_specs('F', ft_split(line, ','), specs);
	else if (!ft_strncmp(line, "C ", 2))
		color_specs('C', ft_split(line, ','), specs);
	else if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) ||
			!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		texture_specs(line, specs);
	else if (are_specs_complete(specs))
		*specs_completed = 1;
}

void		cub_fill_specs(int fd, t_specs *specs)
{
	char	*ret;
	int		check;
	int		specs_completed;

	specs_completed = 0;
	while ((check = get_next_line(fd, &ret)) >= 0)
	{
		check_line(ret, specs, &specs_completed);
		free(ret);
		if (specs_completed == 1)
			break ;
		if (check == 0)
			ft_error("Incomplete configuration\n");
	}
}
