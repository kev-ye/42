/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 16:02:15 by besellem          #+#    #+#             */
/*   Updated: 2021/04/25 18:43:52 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

unsigned long long	ft_find_next_prime(unsigned long long nb)
{
	unsigned long long	f;

	if (nb <= 2)
		return (2ULL);
	if (ft_isprime(nb))
		return (nb);
	f = nb + 1 + (nb % 2 == 1);
	while (!ft_isprime(f))
		f += 2;
	return (f);
}
