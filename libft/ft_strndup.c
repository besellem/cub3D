/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 18:20:21 by besellem          #+#    #+#             */
/*   Updated: 2020/11/16 23:40:12 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*cpy;
	size_t	len;
	size_t	i;

	if (n == 0)
		return (NULL);
	i = ft_strlen(s1);
	len = i >= n ? n : i;
	if (!(cpy = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		cpy[i] = s1[i];
		++i;
	}
	cpy[i] = '\0';
	return (cpy);
}
