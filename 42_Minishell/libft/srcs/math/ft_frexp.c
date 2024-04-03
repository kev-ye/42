/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frexp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 21:09:31 by besellem          #+#    #+#             */
/*   Updated: 2021/04/18 21:16:10 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

float	ft_frexpf(float value, int *exp)
{
	float	tmp;

	*exp = 0;
	if (value == 0.0f)
		return (ft_copysignf(0.0f, value));
	if (ft_isinff(value) || ft_isnanf(value))
		return (value);
	tmp = ft_fabsf(value);
	if (tmp >= 0.5f)
	{
		while (!(tmp >= 0.5f && tmp < 1.0f))
		{
			tmp /= 2.0f;
			*exp += 1;
		}
	}
	else
	{
		while (!(tmp >= 0.5f && tmp < 1.0f))
		{
			tmp *= 2.0f;
			*exp -= 1;
		}
	}
	return (ft_copysignf(tmp, value));
}

double	ft_frexp(double value, int *exp)
{
	double	tmp;

	*exp = 0;
	if (value == 0.0)
		return (ft_copysign(0.0, value));
	if (ft_isinf(value) || ft_isnan(value))
		return (value);
	tmp = ft_fabs(value);
	if (tmp >= 0.5)
	{
		while (!(tmp >= 0.5 && tmp < 1.0))
		{
			tmp /= 2.0;
			*exp += 1;
		}
	}
	else
	{
		while (!(tmp >= 0.5 && tmp < 1.0))
		{
			tmp *= 2.0;
			*exp -= 1;
		}
	}
	return (ft_copysign(tmp, value));
}

long double	ft_frexpl(long double value, int *exp)
{
	long double	tmp;

	*exp = 0;
	if (value == 0.0L)
		return (ft_copysignl(0.0L, value));
	if (ft_isinfl(value) || ft_isnanl(value))
		return (value);
	tmp = ft_fabsl(value);
	if (tmp >= 0.5L)
	{
		while (!(tmp >= 0.5L && tmp < 1.0L))
		{
			tmp /= 2.0L;
			*exp += 1;
		}
	}
	else
	{
		while (!(tmp >= 0.5L && tmp < 1.0L))
		{
			tmp *= 2.0L;
			*exp -= 1;
		}
	}
	return (ft_copysignl(tmp, value));
}
