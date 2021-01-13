/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 20:37:56 by besellem          #+#    #+#             */
/*   Updated: 2020/11/27 15:04:38 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

int	ft_vdprintf(int fd, const char *format, va_list ap)
{
	int size;

	size = ft_process(format, ap, fd);
	return (size);
}
