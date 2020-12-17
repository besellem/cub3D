/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 22:41:58 by besellem          #+#    #+#             */
/*   Updated: 2020/12/17 02:05:57 by besellem         ###   ########.fr       */
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

static int	convert_map(t_list **lst, t_cub *cub, size_t pos[2])
{
	t_list	**head;
	int		i;

	head = lst;
	if (!(cub->map = (char **)malloc(sizeof(char *) * (pos[1] + 1))))
		return (0);
	i = -1;
	while (*head)
	{
		if (!(cub->map[++i] = (char *)malloc(sizeof(char) * (pos[0] + 1))))
			return (0);
		fill_map_line(cub->map[i], (*head)->content, pos[0]);
		head = &(*head)->next;
	}
	cub->map[++i] = NULL;
	ft_lstclear(lst, free);
	return (1);
}

void		parse_map(int fd, t_cub *cub)
{
	t_list	*lst;
	t_list	*tmp_lst;
	char	*ret;
	int		check;
	size_t	pos[2];

	pos[0] = 0;
	pos[1] = 0;
	lst = NULL;
	while ((check = get_next_line(fd, &ret)) >= 0)
	{
		ft_printf("HERE\n");
		if (!(tmp_lst = ft_lstnew(ret)))
		{
			ft_lstclear(&lst, free);
			ft_error("Malloc error in map parsing", cub, __FILE__, __LINE__);
		}
		if (pos[0] < ft_strlen(ret))
			pos[0] = ft_strlen(ret);
		++pos[1];
		ft_lstadd_back(&lst, tmp_lst);
		if (check == 0 && convert_map(&lst, cub, pos))
			break ;
	}
	ft_error("No map found !", cub, __FILE__, __LINE__);
}
