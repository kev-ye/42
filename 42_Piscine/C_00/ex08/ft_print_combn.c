/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 10:44:17 by kaye              #+#    #+#             */
/*   Updated: 2020/08/06 11:25:56 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_print(int *tab, int n)
{
	int i;
	int print;

	i = 0;
	print = 1;
	while (i < n - 1)
	{
		if (tab[i] >= tab[i + 1])
			print = 0;
		i++;
	}
	i = 0;
	if (print == 1)
	{
		while (i < n)
		{
			ft_putchar(tab[i] + '0');
			i++;
		}
		if (tab[0] < 10 - n)
			write(1, ", ", 2);
	}
}

void	ft_print_combn(int n)
{
	int i;
	int tab[10];

	i = -1;
	if (n <= 0 || n >= 10)
		return ;
	while (++i < n)
		tab[i] = i;
	while (tab[0] <= 10 - n)
	{
		ft_print(tab, n);
		tab[n - 1]++;
		i = n - 1;
		while (i != 0)
		{
			if (tab[i] == 10)
			{
				tab[i - 1]++;
				tab[i] = 0;
			}
			i--;
		}
	}
}
