/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 19:56:18 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 18:16:30 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static int	with_prec(char *conv, int prec)
{
	int		count;
	size_t	len;

	count = 0;
	len = ft_strlen(conv);
	if (prec >= 0)
	{
		count += ft_putstr_pf("0x");
		count += ft_parse_width(prec, len, 1);
	}
	count += ft_putstr_pf(conv);
	return (count);
}

static int	parse_pointer(char *conv, t_flag flag)
{
	int		count;
	size_t	len;

	count = 0;
	len = ft_strlen(conv);
	if (flag.prec >= 0 && (size_t)flag.prec < len)
		flag.prec = len;
	if (flag.minus)
		count += with_prec(conv, flag.prec);
	if (flag.prec >= 0)
		count += ft_parse_width(flag.width, flag.prec + 2, 0);
	else
	{
		count += ft_parse_width(flag.width, len + 2, flag.zero);
		if (!flag.zero && !flag.minus)
			count += ft_putstr_pf("0x");
	}
	if (!flag.minus)
		count += with_prec(conv, flag.prec);
	return (count);
}

int	ft_parse_pointer(void *p, t_flag flag)
{
	char	*conv;
	int		count;

	count = 0;
	if ((unsigned long long)p == 0 && flag.prec == 0)
	{
		if (flag.minus)
			count += ft_putstr_pf("0x");
		count += ft_parse_width(flag.width, 2, 0);
		if (!flag.minus)
			count += ft_putstr_pf("0x");
		return (count);
	}
	if ((flag.zero || flag.minus) && flag.prec < 0)
		count += ft_putstr_pf("0x");
	conv = ft_ulltoa_base_pf((unsigned long long)p, 16, 0);
	count += parse_pointer(conv, flag);
	free(conv);
	return (count);
}
