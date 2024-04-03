/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 11:26:40 by kaye              #+#    #+#             */
/*   Updated: 2020/08/20 11:28:17 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_print_hex(unsigned char nb)
{
	char				*hex;

	hex = "0123456789abcdef";
	ft_putchar(hex[nb / 16]);
	ft_putchar(hex[nb % 16]);
}

void	ft_print_line(char *str, unsigned int size)
{
	unsigned int		i;

	i = 0;
	while (i < size)
	{
		if ((i % 2) == 0)
			ft_putchar(' ');
		ft_print_hex(str[i]);
		i++;
	}
	while (i < 16)
	{
		write(1, "   ", (i % 2) ? 2 : 3);
		i++;
	}
	ft_putchar(' ');
	i = 0;
	while (i < size)
	{
		ft_putchar((str[i] < 32 || str[i] == 127) ? '.' : str[i]);
		i++;
	}
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	unsigned int		i;
	int					j;

	i = 0;
	while (i < size)
	{
		j = 56;
		while (j >= 0)
		{
			ft_print_hex(((unsigned long)addr + i) >> j);
			j = j - 8;
		}
		ft_putchar(':');
		ft_print_line(addr + i, ((size - i) > 16) ? 16 : (size - i));
		ft_putchar('\n');
		i = i + 16;
	}
	return (addr);
}
