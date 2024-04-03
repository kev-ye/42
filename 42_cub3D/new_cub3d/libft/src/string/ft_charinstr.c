/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charinstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 11:20:22 by kaye              #+#    #+#             */
/*   Updated: 2021/03/09 19:51:51 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Computes the number of char found in strings.
*/

size_t	ft_charinstr(char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			++count;
		++s;
	}
	return (count);
}
