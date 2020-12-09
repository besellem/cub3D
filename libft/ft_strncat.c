/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 18:58:23 by besellem          #+#    #+#             */
/*   Updated: 2020/11/16 23:40:14 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t len;
	size_t i;

	len = ft_strlen(s1);
	i = 0;
	while (s2[i] && i < n)
	{
		s1[len + i] = s2[i];
		++i;
	}
	s1[len + i] = '\0';
	return (s1);
}
