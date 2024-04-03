/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_row_and_col_with_condition.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 17:17:29 by kaye              #+#    #+#             */
/*   Updated: 2020/08/16 19:39:42 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rush.h"

int		ft_check_raw_left_with_condition(int raw, int **tab, int *condition)
{
	int number_bigger;
	int condition_adapt;
	int number_actuel;

	number_bigger = 0;
	condition_adapt = 0;
	number_actuel = 0;
	while (number_actuel < 4)
	{
		if (tab[raw][number_actuel] > number_bigger)
		{
			number_bigger = tab[raw][number_actuel];
			condition_adapt++;
		}
		if (tab[raw][number_actuel] == 0)
			return (1);
		number_actuel++;
	}
	if (condition[raw + 8] != condition_adapt)
		return (0);
	return (1);
}

int		ft_check_raw_right_with_condition(int raw, int **tab, int *condition)
{
	int number_bigger;
	int condition_adapt;
	int number_actuel;

	number_actuel = 3;
	number_bigger = 0;
	condition_adapt = 0;
	while (number_actuel >= 0)
	{
		if (tab[raw][number_actuel] > number_bigger)
		{
			number_bigger = tab[raw][number_actuel];
			condition_adapt++;
		}
		if (tab[raw][number_actuel] == 0)
			return (1);
		number_actuel--;
	}
	if (condition[raw + 12] != condition_adapt)
		return (0);
	return (1);
}

int		ft_check_col_up_with_condition(int col, int **tab, int *condition)
{
	int number_bigger;
	int condition_adapt;
	int number_actuel;

	number_bigger = 0;
	condition_adapt = 0;
	number_actuel = 0;
	while (number_actuel < 4)
	{
		if (tab[number_actuel][col] > number_bigger)
		{
			number_bigger = tab[number_actuel][col];
			condition_adapt++;
		}
		if (tab[number_actuel][col] == 0)
			return (1);
		number_actuel++;
	}
	if (condition[col] != condition_adapt)
		return (0);
	return (1);
}

int		ft_check_col_down_with_condition(int col, int **tab, int *condition)
{
	int number_bigger;
	int condition_adapt;
	int number_actuel;

	number_actuel = 3;
	number_bigger = 0;
	condition_adapt = 0;
	while (number_actuel >= 0)
	{
		if (tab[number_actuel][col] > number_bigger)
		{
			number_bigger = tab[number_actuel][col];
			condition_adapt++;
		}
		if (tab[number_actuel][col] == 0)
			return (1);
		number_actuel--;
	}
	if (condition[col + 4] != condition_adapt)
		return (0);
	return (1);
}
