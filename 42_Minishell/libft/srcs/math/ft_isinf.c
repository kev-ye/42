/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:06:27 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 14:37:45 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "ft_string.h"

int	ft_isinff(float x)
{
	uint32_t	input;

	ft_memcpy(&input, &x, sizeof(float));
	return (input == 0x7F800000 || input == 0xFF800000);
}

int	ft_isinf(double x)
{
	uint64_t	input;

	ft_memcpy(&input, &x, sizeof(double));
	return (input == 0x7FF0000000000000LL || input == 0xFFF0000000000000LL);
}

int	ft_isinfl(long double x)
{
	union u_dbl80	u;

	u.ld = x;
	return ((u.s_xtr.exp == 0x7FFF || u.s_xtr.exp == 0xFFFF)
		&& u.s_xtr.m == 0x8000000000000000);
}
