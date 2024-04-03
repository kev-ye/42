/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_for_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 11:25:55 by kaye              #+#    #+#             */
/*   Updated: 2020/08/27 11:26:02 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_free_for_all(int **tab, int **stock, t_solver solver)
{
	int i;

	i = 0;
	while (tab[i] != 0)
	{
		if (tab[i] != 0)
			free(tab[i]);
		i++;
	}
	i = 0;
	while (stock[i] != 0)
	{
		if (stock[i] != 0)
			free(stock[i]);
		i++;
	}
	if (solver.string_tray != 0)
		free(solver.string_tray);
}
