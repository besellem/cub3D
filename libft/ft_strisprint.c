/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 12:41:19 by besellem          #+#    #+#             */
/*   Updated: 2021/01/13 12:54:35 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Check if each characters of the string are printable
*/

int	ft_strisprint(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]) == 0)
			return (0);
		++i;
	}
	return (1);
}
