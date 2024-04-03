/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ceil.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 11:22:27 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 13:33:32 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "ft_string.h"

float	ft_ceilf(float f)
{
	uint32_t	input;
	uint32_t	output;
	int			exponent;
	int			fractional_bits;

	ft_memcpy(&input, &f, sizeof(float));
	exponent = ((input >> 23) & 255) - 127;
	if (exponent < 0)
		return (ft_copysignf((f > 0), f));
	fractional_bits = 23 - exponent;
	if (fractional_bits <= 0)
		return (f);
	output = input & (0xffffffff << fractional_bits);
	ft_memcpy(&f, &output, sizeof(float));
	if (f > 0 && output != input)
		++f;
	return (f);
}

double	ft_ceil(double f)
{
	uint64_t	input;
	uint64_t	output;
	int			exponent;
	int			fractional_bits;

	ft_memcpy(&input, &f, sizeof(double));
	exponent = ((input >> 52) & 2047) - 1023;
	if (exponent < 0)
		return (ft_copysign((f > 0), f));
	fractional_bits = 52 - exponent;
	if (fractional_bits <= 0)
		return (f);
	output = input & (0xffffffffffffffff << fractional_bits);
	ft_memcpy(&f, &output, sizeof(double));
	if (f > 0 && output != input)
		++f;
	return (f);
}
