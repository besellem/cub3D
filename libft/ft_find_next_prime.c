/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 16:02:15 by besellem          #+#    #+#             */
/*   Updated: 2020/11/16 23:40:25 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_find_next_prime(int nb)
{
	int f;

	if (ft_is_prime(nb))
		return (nb);
	f = nb + 1;
	while (!ft_is_prime(f))
		++f;
	return (f);
}
