/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 21:23:11 by besellem          #+#    #+#             */
/*   Updated: 2021/02/02 21:25:26 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Replace ternary operation (because of norm v3)
*/

void	*ft_ternary(int condition, void *if_true, void *if_false)
{
	if (condition != 0)
		return (if_true);
	else
		return (if_false);
}
