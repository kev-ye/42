/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 19:40:53 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 19:59:19 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static int	with_prec(char *s, int prec)
{
	int		count;

	count = 0;
	if (prec >= 0)
		count += ft_putstr_prec_pf(s, prec);
	else
		count += ft_putstr_pf(s);
	return (count);
}

int	ft_parse_string(char *s, t_flag flag)
{
	int		count;
	size_t	len;

	if (!s)
		s = "(null)";
	count = 0;
	len = ft_strlen(s);
	if (flag.prec >= 0 && (size_t)flag.prec > len)
		flag.prec = len;
	if (flag.minus)
		count += with_prec(s, flag.prec);
	if (flag.prec >= 0)
		count += ft_parse_width(flag.width, flag.prec, flag.zero);
	else
		count += ft_parse_width(flag.width, len, flag.zero);
	if (!flag.minus)
		count += with_prec(s, flag.prec);
	return (count);
}
