/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 02:42:55 by besellem          #+#    #+#             */
/*   Updated: 2021/05/19 22:30:11 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

int	f_prec(char **ret, long double n, int precision, int sign)
{
	char	*data;
	int		i;

	if (precision == 0)
		return (prec_zero_case(n, sign));
	data = (char *)ft_calloc(precision + 2, sizeof(char));
	if (!data)
		return (0);
	i = -1;
	data[++i] = '.';
	n = ft_trnld((sign), -n + (long)n, n - (long)n);
	while (i < precision)
	{
		n = (n * 10) - (((long)n % 10) * 10);
		data[++i] = (long)n % 10 + 48;
	}
	data[++i] = '\0';
	i = 0;
	if (((long)((n * 10) - (((long)n % 10) * 10)) % 10) >= 5)
		i = ft_round_str(data, precision);
	*ret = data;
	return (i);
}

char	*convert_f(long double n, int prec, int htag, int sign)
{
	char	*data;
	char	*nbr;
	char	*pr;
	int		len;

	pr = NULL;
	prec = ft_trni((prec < 0), 6, prec);
	if (sign)
		n += -f_prec(&pr, n, prec, sign);
	else
		n += f_prec(&pr, n, prec, sign);
	nbr = convert_to_float((long long)n, sign);
	len = ft_strlen(nbr) + prec + (prec == 0 && htag);
	data = (char *)ft_calloc(len + 1, sizeof(char));
	if (!data)
		return (NULL);
	ft_strcat(data, nbr);
	if (prec == 0 && htag)
		ft_strcat(data, ".");
	if (pr)
		ft_strcat(data, pr);
	ft_free(2, nbr, pr);
	return (data);
}

char	*conv_add_zf(t_indicators t, char *data, int s)
{
	char	*z;
	int		len;
	int		sign_len;

	z = NULL;
	len = ft_trni((data != NULL), ft_strlen(data), 0);
	sign_len = (s || t.plus || t.space);
	if (t.zero > 0 && t.minus == -1)
	{
		len = ft_trni((t.zero + s > (int)len), t.zero - len - sign_len, 0);
		z = ft_malloc_c(ft_trni((len > 0), len, 0), '0');
	}
	return (z);
}

char	*conv_f(t_indicators t, long double n, int sign)
{
	char	*r;
	char	*sp;

	if (ft_isnanl(n))
		r = ft_strdup("nan");
	else
	{
		if (ft_isinfl(n))
			r = ft_strdup("inf");
		else
		{
			r = convert_f(n, t.dot, t.htag, sign);
			r = ft_mcat(conv_add_zf(t, r, sign), r);
		}
		r = ft_mcat(conv_add_sign(t, sign), r);
	}
	sp = NULL;
	if (t.zero >= 0 || t.width >= 0)
		sp = space_padding(r, ft_trni((t.width >= 0), t.width, t.zero));
	if (t.minus == -1)
		r = ft_mcat(sp, r);
	else if (t.minus == 1)
		r = ft_mcat(r, sp);
	return (r);
}

void	ft_alloc_f(t_data **s, t_indicators t, va_list ap)
{
	char		*data;
	long double	n;

	n = f_spec(&t, ap);
	data = conv_f(t, n, ft_signbitl(n));
	add_lstd(s, data);
	ft_free(1, data);
}
