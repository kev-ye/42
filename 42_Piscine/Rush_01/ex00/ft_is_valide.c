/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valide.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 17:47:33 by kaye              #+#    #+#             */
/*   Updated: 2020/08/18 16:14:12 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rush.h"

int		ft_is_valide(int **tab, int position, int *condition)
{
	t_variables var;

	if (position == 4 * 4)
		return (1);
	var.raw = position / 4;
	var.col = position % 4;
	if (tab[var.raw][var.col] != 0)
		return (ft_is_valide(tab, position + 1, condition));
	var.number = 0;
	while (++var.number <= 4)
	{
		if (ft_check_col(var.number, var.col, tab) &&
				ft_check_raw(var.number, var.raw, tab))
		{
			tab[var.raw][var.col] = var.number;
			if (ft_check_col_up_with_condition(var.col, tab, condition) &&
					ft_check_col_down_with_condition(var.col, tab, condition) &&
					ft_check_raw_left_with_condition(var.raw, tab, condition) &&
					ft_check_raw_right_with_condition(var.raw, tab, condition))
				if (ft_is_valide(tab, position + 1, condition))
					return (1);
		}
	}
	tab[var.raw][var.col] = 0;
	return (0);
}
