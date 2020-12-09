/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_hex_maj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 16:23:35 by besellem          #+#    #+#             */
/*   Updated: 2020/11/27 14:52:38 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

void	ft_alloc_hex_maj(t_data **s, t_indicators t, va_list ap)
{
	char				*data;
	unsigned long long	n;

	n = u_spec(&t, ap);
	data = conv_x(t, n, 0);
	ft_strupcase(data);
	add_lstd(s, data);
	ft_free(1, data);
}
