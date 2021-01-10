/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 14:56:39 by besellem          #+#    #+#             */
/*   Updated: 2020/08/05 14:56:40 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ft_print_hex2(unsigned char nb)
{
	char *base;

	base = "0123456789abcdef";
	write(1, &base[nb / 16], 1);
	write(1, &base[nb % 16], 1);
}

static void	ft_putnbr_hex(unsigned long nbr)
{
	unsigned long	div;
	char			*base;

	base = "0123456789abcdef";
	div = 16;
	while (nbr / div >= 16)
		div *= 16;
	while (div > 0)
	{
		write(1, &base[nbr / div], 1);
		nbr %= div;
		div /= 16;
	}
}

static void	ft_print_hex(char *str, unsigned int *size)
{
	unsigned int i;
	unsigned int len;

	i = 0;
	len = 0;
	while (i < 16 && i < *size)
	{
		ft_print_hex2(str[i]);
		if ((len += 2) && i % 2 == 1 && ++len)
			write(1, " ", 1);
		++i;
	}
	while (++len <= 40)
		write(1, " ", 1);
	i = 0;
	while (i < 16 && i < *size)
	{
		if (str[i] < 32 || str[i] == 127)
			write(1, ".", 1);
		else
			write(1, &str[i], 1);
		++i;
	}
	*size -= i;
}

void		*ft_print_memory(void *addr, unsigned int size)
{
	unsigned int	len;
	int				i;
	char			*str;

	if (size == 0)
		return (addr);
	str = (char *)addr;
	len = 0;
	while (len < size)
	{
		if ((len++ % 16) == 0 || size < 16)
		{
			i = 64;
			while ((i -= 8) >= 0)
				ft_putnbr_hex((((unsigned long)str + i) >> i) % 256);
			write(1, ": ", 2);
			ft_print_hex(str, &size);
			write(1, "\n", 1);
			str += 16;
			len = 0;
		}
	}
	return (addr);
}
