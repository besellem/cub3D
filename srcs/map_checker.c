/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 00:26:39 by besellem          #+#    #+#             */
/*   Updated: 2020/12/18 01:42:40 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		in_charset(char *charset, int c)
{
	size_t i;

	if (!charset)
		return (0);
	i = 0;
	while (charset[i])
		if (charset[i++] == (char)c)
			return (1);
	return (0);
}

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

int				is_valid_charset(t_cub *cub, t_map_checker *mcheck)
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
		}
		j = -1;
		while (cub->map[i][++j])
			if (!in_charset(MAP_CHARSET, cub->map[i][j]))
				return (0);
	}
	return (1);
}

int				check_map(t_cub *cub)
{
	t_map_checker mcheck;

	mcheck.got_player_pos = 0;
	if (!is_valid_charset(cub, &mcheck))
		ft_error("Invalid map", cub, __FILE__, __LINE__);
	return (1);
}
