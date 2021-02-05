/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 01:05:19 by besellem          #+#    #+#             */
/*   Updated: 2021/02/04 23:21:11 by besellem         ###   ########.fr       */
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
	i = -1;
	while (++i < TEXTURES_COUNT && cub->txtrs[i].ptr)
		mlx_destroy_image(cub->mlx, cub->txtrs[i].ptr);
}

/*
** cub->win pointer is not freed here because it's done by mlx_destroy_window()
*/

void		ft_free_cub(t_cub *cub)
{
	int i;

	free_textures(cub);
	if (cub->map)
		ft_free_strs(cub->map);
	if (cub->img.ptr)
		mlx_destroy_image(cub->mlx, cub->img.ptr);
	if (cub->txtr_gun.ptr)
		mlx_destroy_image(cub->mlx, cub->txtr_gun.ptr);
	if (cub->rays)
	{
		i = -1;
		while (++i < cub->win_h)
			free((&cub->rays[i])->sp_ray);
		free(cub->rays);
	}
	if (cub->sprites)
		free(cub->sprites);
	if (cub->mlx)
		free(cub->mlx);
	if (BONUS)
	{
		system("killall "SOUND_CMD" 2>/dev/null");
	}
}

/*
** Check the extension name of a file
*/

int			file_got_ext(char *file, char *extension)
{
	size_t file_len;
	size_t ext_len;

	if (!file || !extension)
		return (0);
	file_len = ft_strlen(file);
	ext_len = ft_strlen(extension);
	if (file_len < ext_len)
		return (0);
	return (ft_strncmp(file + file_len - ext_len, extension, ext_len) == 0);
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
