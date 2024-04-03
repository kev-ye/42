/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 15:46:45 by besellem          #+#    #+#             */
/*   Updated: 2021/04/18 21:16:10 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

/*
** This implementation is not correctly rounded like the real round() function.
** This value does not work for example:
**
** #include <stdio.h>
** #include <math.h>
**
** double value = -1.49999999999999994;
** printf("real: %f\n", round(value));
** printf("test: %f\n", ft_round(value));
**
**     OR
**
** float value = -1.499999994f;
** printf("real: %f\n", roundf(value));
** printf("test: %f\n", ft_roundf(value));
**
**
** Prints:
** real: -2.000000
** test: -1.000000
*/

float	ft_roundf(float x)
{
	const float	ceil_val = ft_ceilf(x);

	if ((ceil_val - x) <= 0.5f)
		return (ceil_val);
	else
		return (ceil_val - 1.0f);
}

double	ft_round(double x)
{
	const double	ceil_val = ft_ceil(x);

	if ((ceil_val - x) <= 0.5)
		return (ceil_val);
	else
		return (ceil_val - 1.0);
}
