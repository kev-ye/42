/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lround.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:08:43 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 13:35:18 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

/*
** This implementation is not correctly rounded like the real lround() function.
** This value does not work for example:
**
** #include <stdio.h>
** #include <math.h>
**
** double value = -1.49999999999999994;
** printf("real: %ld\n", lround(value));
** printf("test: %ld\n", ft_lround(value));
**
**     OR
**
** float value = -1.499999994f;
** printf("real: %ld\n", lroundf(value));
** printf("test: %ld\n", ft_lroundf(value));
**
**
** Prints:
** real: -2
** test: -1
*/

long int	ft_lroundf(float x)
{
	const float	ceil_val = ft_ceilf(x);

	if (x >= INT64_MAX)
		return (INT64_MAX);
	if ((ceil_val - x) <= 0.5f)
		return ((long int)ceil_val);
	else
		return ((long int)(ceil_val - 1.0f));
}

long int	ft_lround(double x)
{
	const double	ceil_val = ft_ceil(x);

	if (x >= INT64_MAX)
		return (INT64_MAX);
	if ((ceil_val - x) <= 0.5)
		return ((long int)ceil_val);
	else
		return ((long int)(ceil_val - 1.0));
}
