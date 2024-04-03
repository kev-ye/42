/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nblen_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 13:04:36 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 11:14:14 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"

int	ft_nblen_base(long long n, int base)
{
	int	len;

	if (n < 0)
		n = -n;
	len = 1;
	while (n / base > 0)
	{
		n /= base;
		++len;
	}
	return (len);
}
