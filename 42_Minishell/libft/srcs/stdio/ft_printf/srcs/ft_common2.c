/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_common2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 20:19:44 by besellem          #+#    #+#             */
/*   Updated: 2021/05/19 21:44:43 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

void	*ft_malloc_c(size_t size, char c)
{
	char	*str;
	size_t	i;

	if (size <= 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < size)
	{
		str[i] = c;
		++i;
	}
	str[i] = '\0';
	return (str);
}

void	ft_free(size_t nb, ...)
{
	va_list	ap;
	void	*ptr;

	va_start(ap, nb);
	while (nb-- > 0)
	{
		ptr = va_arg(ap, void *);
		if (ptr)
			free(ptr);
	}
	va_end(ap);
}

char	*conv_add_z(t_indicators t, char *data, t_ull n, int s)
{
	char	*z;
	int		len;
	int		sign_len;

	z = NULL;
	len = ft_trnul((data != NULL), ft_strlen(data), 0);
	sign_len = (s || t.plus || t.space);
	if (t.dot >= 0)
	{
		len = ft_trni(((int)len > t.dot), 0, t.dot - len);
		z = ft_malloc_c(ft_trni((n == 0 && t.dot == 0), 0, len), '0');
	}
	else if (t.zero > 0)
	{
		len = ft_trni((t.zero + s > (int)len), t.zero - len - sign_len, 0);
		z = ft_malloc_c(ft_trni((len < 0), 0, len), '0');
	}
	return (z);
}

char	*conv_add_sign(t_indicators t, int sign)
{
	char	*sgn;

	sgn = NULL;
	if (sign == 0 && t.plus)
		sgn = ft_strdup("+");
	else if (sign == 1)
		sgn = ft_strdup("-");
	else if (sign == 0 && t.space == 1)
		sgn = ft_strdup(" ");
	return (sgn);
}

char	*conv_d(t_indicators t, t_ull n, int sign, char *base)
{
	char	*r;
	char	*sp;

	r = NULL;
	if (!(n == 0 && t.dot == 0))
		r = convert_base_u(n, base);
	r = ft_mcat(conv_add_z(t, r, n, sign), r);
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
