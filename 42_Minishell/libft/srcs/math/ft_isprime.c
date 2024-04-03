/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 16:02:26 by besellem          #+#    #+#             */
/*   Updated: 2021/04/25 18:40:21 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

int	ft_isprime(unsigned long long nb)
{
	unsigned long long	_sqrt;
	unsigned long long	f;

	if (nb < 2)
		return (0);
	if (nb % 2 == 0)
		return (nb == 2);
	_sqrt = (unsigned long long)ft_sqrt(nb);
	f = 3;
	while (f <= _sqrt)
	{
		if (nb % f == 0)
			return (0);
		f += 2;
	}
	return (1);
}
