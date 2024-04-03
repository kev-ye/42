/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copysign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 11:03:04 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 14:36:16 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "ft_string.h"

float	ft_copysignf(float x, float y)
{
	uint32_t	x_input;
	uint32_t	y_input;

	ft_memcpy(&y_input, &y, sizeof(float));
	ft_memcpy(&x_input, &x, sizeof(float));
	if ((y_input >> 31) == (x_input >> 31))
		return (x);
	else
		return (-x);
}

double	ft_copysign(double x, double y)
{
	uint64_t	x_input;
	uint64_t	y_input;

	ft_memcpy(&y_input, &y, sizeof(double));
	ft_memcpy(&x_input, &x, sizeof(double));
	if ((y_input >> 63) == (x_input >> 63))
		return (x);
	else
		return (-x);
}

long double	ft_copysignl(long double x, long double y)
{
	union u_dbl80	x_u;
	union u_dbl80	y_u;

	x_u.ld = x;
	y_u.ld = y;
	if ((x_u.s_xtr.exp >> 15) == (y_u.s_xtr.exp >> 15))
		return (x);
	else
		return (-x);
}
