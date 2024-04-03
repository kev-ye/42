/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hypot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 23:31:01 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 14:36:54 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

/*
** In the same way as the ft_sqrtl() function,
** ft_hypotl() is not accurate for VERY large numbers
*/
float	ft_hypotf(float x, float y)
{
	const double	_x = (double)x;
	const double	_y = (double)y;

	if (y == 0.0f)
		return (ft_fabsf(x));
	if (ft_isinff(x))
		return (INFINITY);
	return ((float)ft_sqrt(((_x * _x) + (_y * _y))));
}

double	ft_hypot(double x, double y)
{
	const long double	_x = (long double)x;
	const long double	_y = (long double)y;

	if (y == 0.0)
		return (ft_fabs(x));
	if (ft_isinf(x))
		return (INFINITY);
	return ((double)ft_sqrtl(((_x * _x) + (_y * _y))));
}

long double	ft_hypotl(long double x, long double y)
{
	if (y == 0.0L)
		return (ft_fabsl(x));
	if (ft_isinfl(x))
		return (INFINITY);
	return (ft_sqrtl(((x * x) + (y * y))));
}
