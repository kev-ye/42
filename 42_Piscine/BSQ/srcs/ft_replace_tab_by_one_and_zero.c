/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_tab_by_one_and_zero.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiozsert <wiozsert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 10:44:41 by wiozsert          #+#    #+#             */
/*   Updated: 2020/08/27 00:32:42 by wiozsert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		**ft_copy_tab_in_stock(int **tab, int **stock, int emp, int obs)
{
	int i;
	int count;

	i = 0;
	count = -1;
	while (tab[++count] != NULL)
	{
		while (tab[count][i] != '\n')
		{
			if (tab[count][i] == emp)
				stock[count][i] = 1;
			else if (tab[count][i] == obs)
				stock[count][i] = 0;
			i++;
		}
		i = 0;
	}
	return (stock);
}

int		**ft_malloc_tab_in_stock(int **tab, int **stock)
{
	int i;
	int count;

	i = 0;
	count = -1;
	while (tab[++count] != NULL)
	{
		while (tab[count][i] != '\n')
			i++;
		i = 0;
	}
	if (!(stock = (int**)malloc(sizeof(int*) * (count + 1))))
		return (NULL);
	stock[count] = NULL;
	count = -1;
	while (tab[++count] != NULL)
	{
		i = 0;
		while (tab[count][i] != '\n')
			i++;
		if (!(stock[count] = (int*)malloc(sizeof(int) * (i + 1))))
			return (NULL);
		stock[count][i] = '\n';
	}
	return (stock);
}

int		**ft_init_stock(int **stock, int **tab, int empty, int obstacle)
{
	stock = ft_malloc_tab_in_stock(tab, stock);
	stock = ft_copy_tab_in_stock(tab, stock, empty, obstacle);
	return (stock);
}
