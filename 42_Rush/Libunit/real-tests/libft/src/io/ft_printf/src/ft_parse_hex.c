/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 17:38:09 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 18:16:21 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static int	with_prec(char *conv, t_ull ui, int low_up, t_flag flag)
{
	int		count;
	size_t	len;

	count = 0;
	len = ft_strlen(conv);
	if (ui > 0 && flag.hashtag && !flag.zero && flag.prec < 0)
	{
		if (ui > 0 && flag.hashtag && low_up == N_LOW)
			count += ft_putstr_pf("0x");
		else if (low_up == N_UP)
			count += ft_putstr_pf("0X");
	}
	if (flag.prec >= 0)
	{
		if (ui > 0 && flag.hashtag && low_up == N_LOW)
			count += ft_putstr_pf("0x");
		else if (ui > 0 && flag.hashtag && low_up == N_UP)
			count += ft_putstr_pf("0X");
		count += ft_parse_width(flag.prec, len, 1);
	}
	count += ft_putstr_pf(conv);
	return (count);
}

static int	parse_hex(char *conv, t_ull ui, int low_up, t_flag flag)
{
	int		count;
	size_t	len;

	count = 0;
	len = ft_strlen(conv);
	if (flag.prec >= 0 && (size_t)flag.prec < len)
		flag.prec = len;
	if (flag.minus)
		count += with_prec(conv, ui, low_up, flag);
	if (ui > 0 && flag.hashtag)
		flag.width -= 2;
	if (flag.prec >= 0)
		count += ft_parse_width(flag.width, flag.prec, 0);
	else
		count += ft_parse_width(flag.width, len, flag.zero);
	if (!flag.minus)
		count += with_prec(conv, ui, low_up, flag);
	return (count);
}

static int	parse_hex_plus(t_ull ui, int count, int low_up, t_flag flag)
{
	if (ui > 0 && flag.zero && flag.hashtag && flag.prec < 0)
	{
		if (low_up == N_LOW)
			count += ft_putstr_pf("0x");
		else if (low_up == N_UP)
			count += ft_putstr_pf("0X");
	}
	return (count);
}

int	ft_parse_hex(t_ull ui, int low_up, t_flag flag)
{
	char	*conv;
	int		count;

	count = 0;
	if (ui == 0 && flag.prec == 0)
	{
		count += ft_parse_width(flag.width, 0, 0);
		return (count);
	}
	count += parse_hex_plus(ui, count, low_up, flag);
	conv = ft_ulltoa_base_pf(ui, 16, low_up);
	count += parse_hex(conv, ui, low_up, flag);
	free(conv);
	return (count);
}
