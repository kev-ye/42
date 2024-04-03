/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_octal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:53:05 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 18:16:28 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static int	with_prec(char *conv, t_ull ui, t_flag flag)
{
	int		count;
	size_t	len;

	count = 0;
	len = ft_strlen(conv);
	if (ui > 0 && flag.hashtag && !flag.zero && flag.prec < 0)
	{
		if (ui > 0 && flag.hashtag)
			count += ft_putchar_pf('0');
	}
	if (flag.prec >= 0)
	{
		if (ui > 0 && flag.hashtag)
			count += ft_putchar_pf('0');
		count += ft_parse_width(flag.prec, len, 1);
	}
	count += ft_putstr_pf(conv);
	return (count);
}

static int	parse_octal(char *conv, t_ull ui, t_flag flag)
{
	int		count;
	size_t	len;

	count = 0;
	len = ft_strlen(conv);
	if (flag.prec >= 0 && (size_t)flag.prec < len)
		flag.prec = len;
	if (flag.minus)
		count += with_prec(conv, ui, flag);
	if (ui > 0 && flag.hashtag)
		--flag.width;
	if (flag.prec >= 0)
		count += ft_parse_width(flag.width, flag.prec, 0);
	else
		count += ft_parse_width(flag.width, len, flag.zero);
	if (!flag.minus)
		count += with_prec(conv, ui, flag);
	return (count);
}

static int	parse_octal_plus(t_ull ui, int count, t_flag flag)
{
	if (ui > 0 && flag.zero && flag.hashtag && flag.prec < 0)
		count += ft_putchar_pf('0');
	return (count);
}

int	ft_parse_octal(t_ull ui, t_flag flag)
{
	char	*conv;
	int		count;

	count = 0;
	if (ui == 0 && flag.prec == 0)
	{
		count += ft_parse_width(flag.width, 0, 0);
		return (count);
	}
	count += parse_octal_plus(ui, count, flag);
	conv = ft_ulltoa_base_pf(ui, 8, N_LOW);
	count += parse_octal(conv, ui, flag);
	free(conv);
	return (count);
}
