/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fma.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:01:38 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 14:36:29 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

float	ft_fmaf(float x, float y, float z)
{
	if ((ft_isinff(x) || ft_isinff(y)) && (x == 0.0 || y == 0.0))
		return (NAN);
	return ((x * y) + z);
}

double	ft_fma(double x, double y, double z)
{
	if ((ft_isinf(x) || ft_isinf(y)) && (x == 0.0 || y == 0.0))
		return (NAN);
	return ((x * y) + z);
}

long double	ft_fmal(long double x, long double y, long double z)
{
	if ((ft_isinfl(x) || ft_isinfl(y)) && (x == 0.0 || y == 0.0))
		return (NAN);
	return ((x * y) + z);
}
