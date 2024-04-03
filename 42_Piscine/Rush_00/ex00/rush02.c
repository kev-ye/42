/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 10:47:49 by kaye              #+#    #+#             */
/*   Updated: 2020/08/09 20:02:54 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c);

void	ft_print_top(int x)
{
	int i;

	i = 2;
	if (x >= 1)
	{
		ft_putchar('A');
		while (i < x)
		{
			ft_putchar('B');
			i++;
		}
		if (x >= 2)
			ft_putchar('A');
	}
}

void	ft_print_down(int x)
{
	int i;

	i = 2;
	if (x >= 1)
	{
		ft_putchar('C');
		while (i < x)
		{
			ft_putchar('B');
			i++;
		}
		if (x >= 2)
			ft_putchar('C');
	}
}

void	ft_print_mid(int x)
{
	int i;

	i = 2;
	if (x >= 1)
	{
		ft_putchar('B');
		while (i < x)
		{
			ft_putchar(' ');
			i++;
		}
		if (x >= 2)
			ft_putchar('B');
	}
}

void	rush(int x, int y)
{
	int i;

	i = 2;
	if (x >= 1 && y >= 1)
	{
		ft_print_top(x);
		ft_putchar('\n');
		while (i < y)
		{
			ft_print_mid(x);
			ft_putchar('\n');
			i++;
		}
		if (y >= 2)
		{
			ft_print_down(x);
			ft_putchar('\n');
		}
	}
}
