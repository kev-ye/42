/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_tab_from_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiozsert <wiozsert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 12:50:16 by wiozsert          #+#    #+#             */
/*   Updated: 2020/08/27 02:13:41 by wiozsert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int		**ft_copy_str_to_tab(int *str, int **tab)
{
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	count = 0;
	while (str[i - 1] != '\n')
		i++;
	while (str[i] != '\n')
	{
		while (str[i] != '\n')
		{
			tab[count][j] = str[i];
			j++;
			i++;
		}
		count++;
		j = 0;
		i++;
	}
	return (tab);
}

static int		**ft_malloc_str_to_tab(int *str, int **tab, int i, int size)
{
	int count;

	count = 0;
	while (str[i - 1] != '\n')
		i++;
	while (str[i] != '\n')
	{
		while (str[i] != '\n')
		{
			i++;
			size++;
		}
		if (!(tab[count] = (int*)malloc(sizeof(int) * (size + 2))))
			return (NULL);
		tab[count][size] = '\n';
		tab[count][size + 1] = '\0';
		count++;
		size = 0;
		i++;
	}
	return (tab);
}

static int		**ft_malloc_tab_from_str(int *str, int **tab)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (str[i] != '\0')
	{
		if (str[i - 1] == '\n' && str[i] >= 32 && str[i] <= 126)
			size++;
		i++;
	}
	if (!(tab = (int**)malloc(sizeof(int*) * (size + 1))))
		return (NULL);
	tab[size] = NULL;
	return (tab);
}

int				**ft_init_tab_from_str(int *str, int **tab)
{
	tab = ft_malloc_tab_from_str(str, tab);
	tab = ft_malloc_str_to_tab(str, tab, 0, 0);
	tab = ft_copy_str_to_tab(str, tab);
	return (tab);
}
