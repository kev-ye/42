/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 17:11:00 by kaye              #+#    #+#             */
/*   Updated: 2020/08/20 10:22:34 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_stock_str.h"

int						ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char					*ft_strdup(char *src)
{
	char	*save;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen(src);
	if (!(save = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (src[++i])
		save[i] = src[i];
	save[i] = '\0';
	return (save);
}

struct s_stock_str		*ft_strs_to_tab(int ac, char **av)
{
	t_stock_str *stock;
	int			i;

	i = 0;
	stock = (t_stock_str*)malloc(sizeof(t_stock_str) * (ac + 1));
	if (stock == NULL)
		return (NULL);
	while (i < ac)
	{
		stock[i].size = ft_strlen(av[i]);
		stock[i].str = av[i];
		stock[i].copy = ft_strdup(av[i]);
		i++;
	}
	stock[i].size = 0;
	stock[i].str = 0;
	stock[i].copy = 0;
	return (stock);
}
