/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 14:18:42 by kaye              #+#    #+#             */
/*   Updated: 2020/08/24 15:28:57 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		*ft_map(int *tab, int length, int (*f)(int))
{
	int *stock;
	int i;

	i = 0;
	if (!(stock = (int*)malloc(sizeof(int) * length)))
		return (NULL);
	while (i < length)
	{
		stock[i] = (f)(tab[i]);
		i++;
	}
	return (stock);
}
