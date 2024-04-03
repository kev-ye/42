/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_f_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 15:06:12 by besellem          #+#    #+#             */
/*   Updated: 2021/01/12 22:40:00 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

int	ft_round_str(char *str, int precision)
{
	if (precision > 0 && str[precision] == '9')
	{
		str[precision] = '0';
		if (precision == 1 || (precision == 1 && str[precision] >= '5'))
			return (1);
		return (ft_round_str(str, precision - 1));
	}
	else
	{
		str[precision]++;
		return (0);
	}
}

int	prec_zero_case(long double n, int sign)
{
	int		x;
	long	next;

	if (sign)
		n = -n;
	next = ((long)(n * 10) - (((long)n % 10) * 10)) % 10;
	if ((long)n % 2 == 1)
		x = (next >= 5);
	else
		x = (next > 5);
	if (!x && sign)
		return (0);
	return (x);
}
