/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:17:39 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 18:16:42 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

t_flag	ft_init_flag(void)
{
	t_flag	flag;

	flag.minus = 0;
	flag.prec = -1;
	flag.star = 0;
	flag.type = 0;
	flag.width = 0;
	flag.zero = 0;
	flag.space = 0;
	flag.plus = 0;
	flag.hashtag = 0;
	flag.h = 0;
	flag.hh = 0;
	flag.l = 0;
	flag.ll = 0;
	return (flag);
}

int	ft_process(const char *format, va_list arg)
{
	int		i;
	int		count;
	t_flag	flag;

	i = 0;
	count = 0;
	while (format[i])
	{
		flag = ft_init_flag();
		if (format[i] == '%' && format[i + 1])
		{
			i = ft_parse_flags(format, ++i, &flag, arg);
			if (format[i] && ft_type(format[i]))
				count += ft_parse(count, flag.type, arg, flag);
		}
		else if (format[i] != '%')
			count += ft_putchar_pf(format[i]);
		++i;
	}
	return (count);
}
