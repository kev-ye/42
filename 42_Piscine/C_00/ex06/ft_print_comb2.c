/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 19:40:57 by kaye              #+#    #+#             */
/*   Updated: 2020/08/04 18:21:30 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb < 0)
		nb = -nb;
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar(nb + '0');
}

void	ft_print_comb2(void)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 99)
	{
		j = i + 1;
		while (j < 100)
		{
			if (i < 10)
				ft_putchar('0');
			ft_putnbr(i);
			ft_putchar(' ');
			if (j < 10)
				ft_putchar('0');
			ft_putnbr(j);
			if (i != 98)
				write(1, ", ", 2);
			j++;
		}
		i++;
	}
}
