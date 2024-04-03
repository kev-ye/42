/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 16:23:26 by besellem          #+#    #+#             */
/*   Updated: 2021/05/19 21:43:33 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"
#include <stdio.h>
static char	*conv_add_xmiz(t_indicators t, char *d, unsigned long long n, int s)
{
	char	*z;
	int		len;
	int		sign_len;

	z = ft_trns((t.htag && n > 0), ft_strdup("0x"), NULL);
	len = ft_trni((d != NULL), ft_strlen(d), 0);
	sign_len = (s || t.plus || t.space);
	if (t.dot >= 0)
	{
		len = ft_trni(((int)len > t.dot), 0, t.dot - len);
		z = ft_mcat(z, ft_malloc_c(ft_trni(n == 0 && t.dot == 0, 0, len), '0'));
	}
	else if (t.zero > 0)
	{
		len = ft_trni((t.zero + s > (int)len), t.zero - len - sign_len, 0);
		len -= ft_trni((t.htag && n > 0), 2, 0);
		z = ft_mcat(z, ft_malloc_c(ft_trni((len < 0), 0, len), '0'));
	}
	return (z);
}

char	*conv_x(t_indicators t, unsigned long long n, int sign)
{
	char	*r;
	char	*sp;

	r = NULL;
	if (!(n == 0 && t.dot == 0))
		r = convert_base_u(n, "0123456789abcdef");
	r = ft_mcat(conv_add_xmiz(t, r, n, sign), r);
	r = ft_mcat(conv_add_sign(t, sign), r);
	sp = NULL;
	if ((t.dot >= 0 && t.zero >= 0) || t.width >= 0)
		sp = space_padding(r, ft_trni((t.width >= 0), t.width, t.zero));
	if (t.minus == -1)
		r = ft_mcat(sp, r);
	else if (t.minus == 1)
		r = ft_mcat(r, sp);
	return (r);
}

void	ft_alloc_hex_min(t_data **s, t_indicators t, va_list ap)
{
	char				*data;
	unsigned long long	n;

	n = u_spec(&t, ap);
	data = conv_x(t, n, 0);
	add_lstd(s, data);
	ft_free(1, data);
}

void	ft_alloc_hex_maj(t_data **s, t_indicators t, va_list ap)
{
	char				*data;
	unsigned long long	n;

	n = u_spec(&t, ap);
	data = conv_x(t, n, 0);
	ft_strupcase(data);
	add_lstd(s, data);
	ft_free(1, data);
}
