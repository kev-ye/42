/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atold.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 12:15:42 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 11:13:23 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"

long double	ft_atold(const char *str)
{
	long double			nb;
	long double			p;
	unsigned long long	div;
	int					min;

	while (*str && (*str == ' ' || (*str >= '\t' && *str <= '\r')))
		++str;
	min = 1;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			min = -1;
	nb = 0;
	while (*str >= '0' && *str <= '9')
		nb = nb * 10 + *str++ - 48;
	p = 0.;
	if (*str && *str == '.' && ++str)
	{
		div = 1;
		while (*str && *str >= '0' && *str <= '9')
			p = p + ((long double)(*str++ - 48) / (div *= 10));
	}
	return ((nb + p) * min);
}
