/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:38:31 by besellem          #+#    #+#             */
/*   Updated: 2021/05/19 15:52:49 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

static int	edge_cases(double nb, int power, double *res)
{
	if (nb == INFINITY)
	{
		if (power < 0)
			*res = 0.0;
		else
			*res = INFINITY;
	}
	else if (nb == -INFINITY)
	{
		if (power < 0 && (-power % 2) == 1)
			*res = -0.0;
		else if (power < 0 && (-power % 2) == 0)
			*res = 0.0;
		else if (power > 0 && (power % 2) == 1)
			*res = -INFINITY;
		else if (power > 0 && (power % 2) == 0)
			*res = INFINITY;
	}
	else
		return (0);
	return (1);
}

static int	common_cases(double nb, int power, double *res)
{
	if (nb == 1.0)
		*res = 1.0;
	else if (power == 0)
		*res = 1.0;
	else if (nb == 0.0)
	{
		if (power < 0)
			*res = INFINITY;
		else
			*res = 0.0;
	}
	else
		return (0);
	return (1);
}

double	ft_pow(double nb, int power)
{
	double	res;
	double	tmp;

	if (edge_cases(nb, power, &res))
		return (res);
	else if (common_cases(nb, power, &res))
		return (res);
	tmp = nb;
	if (power > 0)
	{
		while (--power > 0)
			nb *= tmp;
	}
	else
	{
		while (++power <= 1)
			nb *= 1.0 / tmp;
	}
	return (nb);
}
