/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:58:04 by kaye              #+#    #+#             */
/*   Updated: 2021/01/20 18:58:11 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates and returns a string representing int received as an argument.
*/

static size_t	ft_intlen(int n)
{
	size_t count;

	if (n != 0)
		count = 0;
	else
		count = 1;
	while (n)
	{
		n = n / 10;
		++count;
	}
	return (count);
}

char			*ft_itoa(int n)
{
	size_t			len;
	char			*str;
	unsigned int	n_tmp;

	if (n < 0)
		n_tmp = -(unsigned int)n;
	else
		n_tmp = n;
	len = (n < 0) ? ft_intlen(n_tmp) + 1 : ft_intlen(n_tmp);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = n_tmp % 10 + '0';
		n_tmp /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
