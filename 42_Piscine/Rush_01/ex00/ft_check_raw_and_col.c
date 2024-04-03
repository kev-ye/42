/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_raw_and_col.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 17:09:43 by kaye              #+#    #+#             */
/*   Updated: 2020/08/16 19:39:29 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rush.h"

int		ft_check_raw(int number, int raw, int **tab)
{
	int col_check;

	col_check = 0;
	while (col_check < 4)
	{
		if (number == tab[raw][col_check])
			return (0);
		col_check++;
	}
	return (1);
}

int		ft_check_col(int number, int col, int **tab)
{
	int raw_check;

	raw_check = 0;
	while (raw_check < 4)
	{
		if (number == tab[raw_check][col])
			return (0);
		raw_check++;
	}
	return (1);
}
