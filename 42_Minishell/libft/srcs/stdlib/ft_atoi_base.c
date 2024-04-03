/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 09:17:00 by besellem          #+#    #+#             */
/*   Updated: 2021/05/07 13:02:48 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"

static int	ft_check_base(char *base)
{
	int	i;
	int	j;

	if (!*base)
		return (0);
	i = -1;
	while (base[++i])
	{
		if (base[i] == '+' || base[i] == '-' || base[i] == ' '
			|| (base[i] >= '\t' && base[i] <= '\r'))
			return (0);
		j = -1;
		while (++j < i)
			if (base[j] == base[i])
				return (0);
	}
	if (i < 2)
		return (0);
	return (i);
}

static int	ft_is_in_base(char c, char *base)
{
	int	i;

	i = -1;
	while (base[++i])
		if (base[i] == c)
			return (i);
	return (-1);
}

static int	ft_alt(char *str, char *base)
{
	int	i;
	int	res;

	res = 0;
	i = -1;
	while (ft_is_in_base(str[++i], base) != -1)
		res = res * ft_check_base(base) + ft_is_in_base(str[i], base);
	return (res);
}

int	ft_atoi_base(char *str, char *base)
{
	int	min;

	if (!ft_check_base(base))
		return (0);
	while (*str && (*str == ' ' || (*str >= '\t' && *str <= '\r')))
		++str;
	min = 1;
	while (*str && (*str == '-' || *str == '+'))
		if (*str++ == '-')
			min *= -1;
	return (ft_alt(str, base) * min);
}
