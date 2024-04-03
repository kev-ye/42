/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trunc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 11:39:34 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 13:35:39 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "ft_string.h"

float	ft_truncf(float x)
{
	uint32_t	input;
	uint32_t	output;
	int			exponent;
	int			fractional_bits;

	ft_memcpy(&input, &x, sizeof(float));
	exponent = ((input >> 23) & 255) - 127;
	if (exponent < 0)
		return (ft_copysignf(0, x));
	fractional_bits = 23 - exponent;
	if (fractional_bits <= 0)
		return (x);
	output = input & (0xffffffff << fractional_bits);
	ft_memcpy(&x, &output, sizeof(float));
	return (x);
}

double	ft_trunc(double x)
{
	uint64_t	input;
	uint64_t	output;
	int			exponent;
	int			fractional_bits;

	ft_memcpy(&input, &x, sizeof(double));
	exponent = ((input >> 52) & 2047) - 1023;
	if (exponent < 0)
		return (ft_copysign(0, x));
	fractional_bits = 52 - exponent;
	if (fractional_bits <= 0)
		return (x);
	output = input & (0xffffffffffffffff << fractional_bits);
	ft_memcpy(&x, &output, sizeof(double));
	return (x);
}
