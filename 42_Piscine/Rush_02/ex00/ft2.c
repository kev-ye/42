/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 19:47:43 by kaye              #+#    #+#             */
/*   Updated: 2020/08/23 20:43:14 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush_02.h"

int		ft_strcmp_nbr(char *s1, char *s2)
{
	int i;

	i = 0;
	while ((s1[i] || s2[i]) && (s1[i] >= '0' && s1[i] <= '9') &&
			(s2[i] >= '0' && s2[i] <= '9'))
	{
		if ((s1[i] || s2[i]) && !(s1[i] == s2[i]))
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

char	*malloc_tab(char *str, char *sep, int i)
{
	char *tab;

	tab = malloc(sizeof(char) * l_entry(str, sep, i) + 1);
	if (tab == NULL)
		return (NULL);
	return (tab);
}

void	print_dic(char *av)
{
	char	*tab;
	char	**dict;
	char	**stock;
	char	*result;
	int		size;

	size = 0;
	tab = ft_open_malloc("numbers.dict");
	dict = ft_split(tab, "\n");
	while (*dict)
	{
		if (to_find(*dict, av))
		{
			stock = ft_split2(*dict, " ");
			size = ft_strlentab(stock);
			result = ft_strjoin(size, stock, " ");
			ft_putstr(result);
			write(1, "\n", 1);
		}
		dict++;
	}
}
