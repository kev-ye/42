/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 11:49:04 by kaye              #+#    #+#             */
/*   Updated: 2020/08/23 19:42:11 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush_02.h"

int		is_space(char c)
{
	return (((c >= '\t' && c <= '\r') && c == ' ') ? 1 : 0);
}

int		is_number(char c)
{
	return ((c >= '0' && c <= '9') ? 1 : 0);
}

int		check_argv_number(char *av)
{
	int i;

	i = 0;
	while (av[i])
	{
		if (!(av[i] >= '0' && av[i] <= '9'))
			return (0);
		else if (av[0] == '0' && (av[i + 1] >= '0' && av[i + 1] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int		check_dic(char *dic)
{
	char	**str;
	int		i;
	int		j;

	i = 0;
	str = ft_split(dic, "\n");
	while (str[i] != NULL)
	{
		j = i + 1;
		while (str[j] != NULL)
		{
			if (ft_strcmp_nbr(str[i], str[j]) == 0)
			{
				ft_error(2);
				return (0);
			}
			j++;
		}
		i++;
	}
	free(str);
	return (1);
}
