/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 13:54:28 by kaye              #+#    #+#             */
/*   Updated: 2020/08/17 19:23:25 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		*ft_range(int min, int max)
{
	int i;
	int len;
	int *tab;

	len = max - min;
	i = 0;
	if (min >= max)
		return (NULL);
	tab = (int*)malloc(sizeof(int) * len);
	if (tab == NULL)
		return (NULL);
	while (i < len)
	{
		tab[i] = min;
		i++;
		min++;
	}
	return (tab);
}
