/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 22:41:58 by besellem          #+#    #+#             */
/*   Updated: 2020/12/18 01:48:12 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_map_line(char *dst, char *content, size_t max)
{
	size_t i;

	i = 0;
	while (content[i])
	{
		dst[i] = content[i];
		++i;
	}
	while (i < max)
		dst[i++] = ' ';
	dst[i] = '\0';
}

/*
** cub->map_size_x => max size of columns in the map
** cub->map_size_y => max size of rows in the map
*/

static int	convert_map(t_list **lst, t_cub *cub)
{
	t_list	**head;
	int		i;

	head = lst;
	if (!(cub->map = (char **)malloc(sizeof(char *) * (cub->map_size_y + 1))))
		return (0);
	i = -1;
	while (*head)
	{
		if (!(cub->map[++i] = (char *)malloc(cub->map_size_x + 1)))
			return (0);
		fill_map_line(cub->map[i], (*head)->content, cub->map_size_x);
		head = &(*head)->next;
	}
	cub->map[++i] = NULL;
	ft_lstclear(lst, free);
	return (1);
}
/*
static void	fill_lst(t_list	**lst, char *ret)
{
	t_list *tmp_lst;

	
}
*/
void		parse_map(int fd, t_cub *cub)
{
	t_list	*lst;
	t_list	*tmp_lst;
	char	*ret;
	int		check;

	lst = NULL;
	while ((check = get_next_line(fd, &ret)) >= 0)
	{
		if (!(tmp_lst = ft_lstnew(ret)))
		{
			ft_lstclear(&lst, free);
			ft_error("Malloc error in map parsing", cub, __FILE__, __LINE__);
		}
		if (++cub->map_size_y && cub->map_size_x < ft_strlen(ret))
			cub->map_size_x = ft_strlen(ret);
		ft_lstadd_back(&lst, tmp_lst);
		if (check == 0 && convert_map(&lst, cub))
			break ;
	}
	if (check == -1)
		ft_error("No map found !", cub, __FILE__, __LINE__);
}
