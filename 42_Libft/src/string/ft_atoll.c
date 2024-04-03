/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 17:21:46 by kaye              #+#    #+#             */
/*   Updated: 2021/03/14 22:34:11 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Converts the string pointed to by str to long long representation.
*/

long long	ft_atoll(const char *str)
{
	int			signe;
	long long	res;

	signe = 1;
	res = 0;
	while (*str && ((*str >= '\t' && *str <= '\r') || (*str == ' ')))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe = -1;
		++str;
	}
	while (*str && ft_isdigit(*str))
	{
		res = res * 10 + *str - '0';
		++str;
	}
	return (res * signe);
}
