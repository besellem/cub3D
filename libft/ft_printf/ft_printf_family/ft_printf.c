/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 21:02:07 by besellem          #+#    #+#             */
/*   Updated: 2020/11/27 15:04:30 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		size;

	va_start(ap, format);
	size = ft_process(format, ap, 1);
	va_end(ap);
	return (size);
}
