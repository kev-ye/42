/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:37:39 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 14:36:22 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

float	ft_fdimf(float x, float y)
{
	float	r;

	if ((x == INFINITY && y == INFINITY) || (x == -INFINITY && y == -INFINITY))
		return (0.0F);
	r = x - y;
	if (r < 0.0)
		return (0.0F);
	return (r);
}

double	ft_fdim(double x, double y)
{
	double	r;

	if ((x == INFINITY && y == INFINITY) || (x == -INFINITY && y == -INFINITY))
		return (0.0);
	r = x - y;
	if (r < 0.0)
		return (0.0);
	return (r);
}

long double	ft_fdiml(long double x, long double y)
{
	long double	r;

	if ((x == INFINITY && y == INFINITY) || (x == -INFINITY && y == -INFINITY))
		return (0.0L);
	r = x - y;
	if (r < 0.0)
		return (0.0L);
	return (r);
}
