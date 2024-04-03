/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:49:39 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 22:05:31 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	get_bigger(t_list *a_b)
{
	t_list	*tmp;
	int		bigger;

	tmp = a_b;
	bigger = (int)tmp->content;
	while (tmp)
	{
		if ((int)tmp->content > bigger)
			bigger = (int)tmp->content;
		tmp = tmp->next;
	}
	return (bigger);
}

int	get_smaller(t_list *a_b)
{
	t_list	*tmp;
	int		smaller;

	tmp = a_b;
	smaller = (int)tmp->content;
	while (tmp)
	{
		if ((int)tmp->content < smaller)
			smaller = (int)tmp->content;
		tmp = tmp->next;
	}
	return (smaller);
}

static void	ft_sort_int_tab(int *tab, int size)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	tmp = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (tab[i] > tab[j])
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	ft_lst_to_tab(int *tab, t_list *a, int size)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = a;
	while (i < size)
	{
		tab[i++] = (int)tmp->content;
		tmp = tmp->next;
	}
}

int	get_median(t_list *a_b, t_stack *stacks, int size)
{
	int	*tab;
	int	median;

	tab = malloc(sizeof(int) * size);
	if (!tab)
		quit_error(stacks, NULL);
	ft_bzero(tab, sizeof(int) * size);
	ft_lst_to_tab(tab, a_b, size);
	ft_sort_int_tab(tab, size);
	median = tab[size / 2];
	free(tab);
	return (median);
}
