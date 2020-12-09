/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 00:59:14 by besellem          #+#    #+#             */
/*   Updated: 2020/11/27 14:52:45 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

void	ft_alloc_i(t_data **s, t_indicators t, va_list ap)
{
	ft_alloc_d(s, t, ap);
}
