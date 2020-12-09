/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_mod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 17:43:58 by besellem          #+#    #+#             */
/*   Updated: 2020/11/27 14:52:47 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

void	ft_alloc_mod(t_data **s, t_indicators t)
{
	char *data;
	char *sp;

	data = "%";
	sp = NULL;
	if (t.zero > 0 && t.minus == 1)
		sp = space_padding(data, t.zero);
	else if (t.zero > 0)
		sp = ft_malloc_c(t.zero - 1, '0');
	if ((t.dot >= 0 && t.zero >= 0) || t.width >= 0)
		sp = space_padding(data, t.width >= 0 ? t.width : t.zero);
	(t.minus == -1) ? add_lstd(s, sp) : 0;
	ft_lstd_add(s, ft_lstd_new(data, 1));
	(t.minus == 1) ? add_lstd(s, sp) : 0;
	ft_free(1, sp);
}
