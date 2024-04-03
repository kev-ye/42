/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifiers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 15:08:33 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 14:47:35 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

long long	d_spec(t_indicators *t, va_list ap)
{
	long long	n;

	if (t->hh)
		n = (char)va_arg(ap, int);
	else if (t->h)
		n = (short)va_arg(ap, int);
	else if (t->l)
		n = (long)va_arg(ap, long);
	else if (t->ll)
		n = va_arg(ap, long long);
	else
		n = va_arg(ap, int);
	return (n);
}

t_ull	u_spec(t_indicators *t, va_list ap)
{
	unsigned long long	n;

	if (t->hh)
		n = (unsigned char)va_arg(ap, unsigned int);
	else if (t->h)
		n = (unsigned short)va_arg(ap, unsigned int);
	else if (t->l)
		n = (unsigned long)va_arg(ap, unsigned long);
	else if (t->ll)
		n = va_arg(ap, unsigned long long);
	else
		n = va_arg(ap, unsigned int);
	return (n);
}

long double	f_spec(t_indicators *t, va_list ap)
{
	long double	n;

	if (t->lf)
		n = va_arg(ap, long double);
	else
		n = (double)va_arg(ap, double);
	return (n);
}
