/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 18:14:12 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 18:16:00 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

size_t	ft_lllen_base_pf(t_ll n, int base)
{
	size_t	count;

	if (n)
		count = 0;
	else
		count = 1;
	while (n)
	{
		n = n / base;
		++count;
	}
	return (count);
}

size_t	ft_uintlen_base_pf(t_uint n, int base)
{
	size_t	count;

	if (n)
		count = 0;
	else
		count = 1;
	while (n)
	{
		n = n / base;
		++count;
	}
	return (count);
}

size_t	ft_ulllen_base_pf(t_ull n, int base)
{
	size_t	count;

	if (n)
		count = 0;
	else
		count = 1;
	while (n)
	{
		n = n / base;
		++count;
	}
	return (count);
}

int	ft_conv_dh_pf(int n, int low_up)
{
	if (n < 10)
		return (n + '0');
	else
	{
		if (low_up)
			return (n - 10 + 'A');
		else
			return (n - 10 + 'a');
	}
}
