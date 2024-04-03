/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 20:44:55 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 18:16:37 by kaye             ###   ########.fr       */
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
		count += ft_parse_width(prec, len, 1);
	count += ft_putstr_pf(conv);
	return (count);
}

static int	parse_uint(char *conv, t_flag flag)
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
		count += ft_parse_width(flag.width, flag.prec, 0);
	else
		count += ft_parse_width(flag.width, len, flag.zero);
	if (!flag.minus)
		count += with_prec(conv, flag.prec);
	return (count);
}

int	ft_parse_uint(t_ull ui, t_flag flag)
{
	char	*conv;
	int		count;

	count = 0;
	if (ui == 0 && flag.prec == 0)
	{
		count += ft_parse_width(flag.width, 0, 0);
		return (count);
	}
	conv = ft_ulltoa_base_pf(ui, 10, 0);
	count += parse_uint(conv, flag);
	free(conv);
	return (count);
}
