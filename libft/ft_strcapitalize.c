/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 14:56:00 by besellem          #+#    #+#             */
/*   Updated: 2020/11/15 12:23:45 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_alphanum(char c)
{
	if ((c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		(c >= '0' && c <= '9'))
		return (1);
	return (0);
}

static int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

static int	is_upper(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

char		*ft_strcapitalize(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (is_upper(str[i]))
			str[i] += 32;
		if (!is_alphanum(str[i - 1]) && is_alpha(str[i]))
			str[i] -= 32;
	}
	return (str);
}
