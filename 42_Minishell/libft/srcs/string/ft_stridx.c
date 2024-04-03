/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stridx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:07:49 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 11:46:31 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** Find the index of the first character from needle that is found in haystack
** If not found, returns -1
*/

int	ft_stridx(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	if (!haystack || !needle)
		return (-1);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (needle[j])
			if (needle[j++] == haystack[i])
				return (i);
		++i;
	}
	return (-1);
}
