/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 23:46:15 by besellem          #+#    #+#             */
/*   Updated: 2020/11/16 23:40:11 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpbrk(const char *s, const char *charset)
{
	size_t i;
	size_t j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (charset[j])
			if (charset[j++] == s[i])
				return ((char *)(s + i));
		++i;
	}
	return (NULL);
}
