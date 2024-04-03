/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 20:28:18 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 18:16:25 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static int	with_prec(char *conv, t_ll i, t_flag flag)
{
	int		count;
	size_t	len;

	count = 0;
	len = ft_strlen(conv);
	if (i < 0 && flag.prec >= 0)
		count += ft_putchar_pf('-');
	if (i >= 0 && flag.plus && !flag.zero && flag.prec < 0)
		count += ft_putchar_pf('+');
	if (flag.prec >= 0)
	{
		if (i >= 0 && flag.space)
			count += ft_putchar_pf(' ');
		else if (i >= 0 && flag.plus)
			count += ft_putchar_pf('+');
		count += ft_parse_width(flag.prec, len, 1);
	}
	count += ft_putstr_pf(conv);
	return (count);
}

static int	parse_int(char *conv, t_ll i, t_flag flag)
{
	int		count;
	size_t	len;

	count = 0;
	len = ft_strlen(conv);
	if (flag.prec >= 0 && (size_t)flag.prec < len)
		flag.prec = len;
	if (flag.minus)
		count += with_prec(conv, i, flag);
	if (i >= 0 && (flag.plus || flag.space))
		--flag.width;
	if (flag.prec >= 0)
		count += ft_parse_width(flag.width, flag.prec, 0);
	else
		count += ft_parse_width(flag.width, len, flag.zero);
	if (!flag.minus)
		count += with_prec(conv, i, flag);
	return (count);
}

static int	parse_int_plus(t_ll i, int count, t_flag flag)
{
	if (i == 0 && flag.prec == 0)
	{
		if (flag.width == 0 && flag.plus)
		{
			count += ft_putchar_pf('+');
			return (count);
		}
		if (flag.plus)
			--flag.width;
		if (flag.plus && flag.minus)
			count += ft_putchar_pf('+');
		count += ft_parse_width(flag.width, 0, 0);
		if (flag.plus && !flag.minus)
			count += ft_putchar_pf('+');
		return (count);
	}
	if (i >= 0 && flag.space && flag.prec < 0)
		if (flag.space)
			count += ft_putchar_pf(' ');
	if (i >= 0 && flag.zero && flag.plus && flag.prec < 0)
		if (flag.plus)
			count += ft_putchar_pf('+');
	return (count);
}

int	ft_parse_int(t_ll i, t_flag flag)
{
	char	*conv;
	int		count;
	t_ll	tmp_i;

	count = 0;
	tmp_i = i;
	if (i == 0 && flag.prec == 0)
	{
		count += parse_int_plus(i, count, flag);
		return (count);
	}
	if (i < 0 && (flag.zero || flag.prec >= 0))
	{
		if (flag.zero && flag.prec < 0)
			count += ft_putchar_pf('-');
		i *= -1;
		--flag.width;
	}
	count = parse_int_plus(tmp_i, count, flag);
	conv = ft_lltoa_base_pf(i, 10);
	count += parse_int(conv, tmp_i, flag);
	free(conv);
	return (count);
}
