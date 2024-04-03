/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gcd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 00:52:03 by besellem          #+#    #+#             */
/*   Updated: 2021/05/16 00:56:39 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

/*
** Euclidean division (greatest common divisor)
** Better way to write it (does not pass the norm):
**
** return ((i % j) == 0 ? j : ft_gcd(j, i % j));
*/

int	ft_gcd(int i, int j)
{
	if ((i % j) == 0)
		return (j);
	return (ft_gcd(j, i % j));
}
