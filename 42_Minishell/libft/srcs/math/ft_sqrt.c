/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 23:02:47 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 14:38:07 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

/*
** Not accurate for VERY large numbers, but will never need numbers this large
** This is quite a good implementation to me.
**
** For the record, I started to see some differences with ft_sqrtl(x), where
** x = LDBL_MAX - (LDBL_MAX / 1.e+20);
*/
float	ft_sqrtf(float x)
{
	return ((float)ft_sqrt((double)x));
}

double	ft_sqrt(double x)
{
	return ((double)ft_sqrtl((long double)x));
}

long double	ft_sqrtl(long double x)
{
	const long double	accuracy_lvl = LDBL_MIN;
	long double			last_accuracy;
	long double			z;
	long double			y;

	if (ft_signbitl(x))
	{
		if (x == 0.0L)
			return (-0.0L);
		else
			return (NAN);
	}
	y = 1.0L;
	z = x;
	last_accuracy = z - y;
	while ((z - y) > accuracy_lvl)
	{
		z = (z + y) / 2.0L;
		y = x / z;
		if ((z - y) == last_accuracy)
			break ;
		last_accuracy = z - y;
	}
	return (z);
}
