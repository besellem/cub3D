/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 01:05:19 by besellem          #+#    #+#             */
/*   Updated: 2020/12/30 23:06:40 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_textures(t_cub *cub)
{
	int i;

	if (cub->txtr_no)
		free(cub->txtr_no);
	if (cub->txtr_so)
		free(cub->txtr_so);
	if (cub->txtr_ea)
		free(cub->txtr_ea);
	if (cub->txtr_we)
		free(cub->txtr_we);
	if (cub->txtr_s)
		free(cub->txtr_s);
	if (cub->txtrs)
	{
		i = -1;
		while (++i < TEXTURES_COUNT && cub->txtrs[i].addr)
			mlx_destroy_image(cub->mlx, cub->txtrs[i].ptr);
		free(cub->txtrs);
	}
}

/*
** cub->win pointer is not freed here because it's done by mlx_destroy_window()
*/

void		ft_free_cub(t_cub *cub)
{
	free_textures(cub);
	if (cub->map)
		ft_free_strs(cub->map);
	if (cub->mlx)
		free(cub->mlx);
	if (cub->img->ptr)
	{
		free(cub->img->ptr);
		free(cub->img->addr);
		free(cub->img);
	}
	if (cub->rays)
		free(cub->rays);
	free(cub->keys);
}

int			file_got_ext(char *file, char *extension)
{
	size_t file_len;
	size_t ext_len;

	file_len = ft_strlen(file);
	ext_len = ft_strlen(extension);
	if (file_len < ext_len)
		return (0);
	if (ft_strncmp(file + file_len - ext_len, extension, ext_len) == 0)
		return (1);
	return (0);
}

int			in_charset(char *charset, int c)
{
	int i;

	if (!charset)
		return (0);
	i = 0;
	while (charset[i])
	{
		if (charset[i] == (char)c)
			return (i);
		++i;
	}
	return (-1);
}

int			charset_in_line(char *line, char *charset)
{
	int i;

	if (!line || !charset)
		return (0);
	i = 0;
	while (line[i])
		if (in_charset(charset, line[i++]) == -1)
			return (0);
	return (1);
}
