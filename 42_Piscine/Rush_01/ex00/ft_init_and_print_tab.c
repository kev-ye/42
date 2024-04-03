/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_and_print_tab.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 17:04:29 by kaye              #+#    #+#             */
/*   Updated: 2020/08/16 18:12:11 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rush.h"

void	ft_print_tab(int **tab)
{
	int		raw;
	int		col;

	raw = 0;
	while (raw < 4)
	{
		col = 0;
		while (col < 4)
		{
			ft_putchar(tab[raw][col] + '0');
			if (col != 3)
				ft_putchar(' ');
			col++;
		}
		ft_putchar('\n');
		raw++;
	}
}

void	ft_init_tab(int **tab)
{
	int		raw;
	int		col;

	raw = 0;
	while (raw < 4)
	{
		col = 0;
		while (col < 4)
		{
			tab[raw][col] = 0;
			col++;
		}
		raw++;
	}
}
