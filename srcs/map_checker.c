/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 00:26:39 by besellem          #+#    #+#             */
/*   Updated: 2020/12/20 02:05:59 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	ft_ocurcs(const char *haystack, char c)
{
	size_t i;
	size_t oc;

	if (!haystack)
		return (0);
	oc = 0;
	i = 0;
	while (haystack[i])
	{
		if (haystack[i] == c)
			++oc;
		++i;
	}
	return (oc);
}

static void		update_pos(t_cub *cub, int x, int y, char pos)
{
	cub->pos_x = x + 0.5;
	cub->pos_y = y + 0.5;
	if (pos == 'E')
		cub->drxion = DRXION_E;
	else if (pos == 'N')
		cub->drxion = DRXION_N;
	else if (pos == 'W')
		cub->drxion = DRXION_W;
	else if (pos == 'S')
		cub->drxion = DRXION_S;
}

static int		check_pos(char *haystack, char *needle)
{
	size_t i;
	size_t j;

	if (!haystack || !needle)
		return (0);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (needle[j])
			if (needle[j++] == haystack[i])
				return (i);
		++i;
	}
	return (0);
}

static int		is_valid_charset(t_cub *cub, t_map_checker *mcheck)
{
	char	*dirxns;
	size_t	tst;
	int		i;
	int		j;

	dirxns = "NEWS";
	i = -1;
	while (cub->map[++i])
	{
		j = -1;
		while (dirxns[++j])
		{
			if ((tst = ft_ocurcs(cub->map[i], dirxns[j])) > 1)
				ft_error("Map contains multiple positions", cub, NULL, 0);
			if (tst == 1 && ++mcheck->got_player_pos > 1)
				return (0);
			if (tst == 1 && mcheck->got_player_pos == 1)
				update_pos(cub, check_pos(cub->map[i], dirxns), i, dirxns[j]);
		}
		j = -1;
		while (cub->map[i][++j])
			if (in_charset(MAP_CHARSET, cub->map[i][j]) == -1)
				return (0);
	}
	return (1);
}

int				check_map(t_cub *cub)
{
	t_map_checker	mcheck;

	mcheck.got_player_pos = 0;
	if (!is_valid_charset(cub, &mcheck))
		ft_error("Invalid map", cub, __FILE__, __LINE__);
	return (1);
}
