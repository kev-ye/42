/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 12:03:47 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 18:16:19 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

t_flag	ft_minus(t_flag flag)
{
	flag.zero = 0;
	flag.minus = 1;
	return (flag);
}

t_flag	ft_width(t_flag flag, va_list arg)
{
	flag.star = 1;
	flag.width = va_arg(arg, int);
	if (flag.width < 0)
	{
		flag.zero = 0;
		flag.minus = 1;
		flag.width *= -1;
	}
	return (flag);
}

t_flag	ft_digit(char format, t_flag flag)
{
	if (flag.star)
	{
		flag.star = 0;
		flag.width = 0;
	}
	flag.width = flag.width * 10 + format - '0';
	return (flag);
}

int	ft_prec(const char *format, int begin_value,
		t_flag *flag, va_list arg)
{
	if (format[begin_value] == '*')
	{
		flag->prec = va_arg(arg, int);
		++begin_value;
	}
	else
	{
		flag->prec = 0;
		while (ft_isdigit(format[begin_value]))
			flag->prec = flag->prec * 10 + format[begin_value++] - '0';
	}
	return (begin_value);
}

int	ft_parse_width(int width, int hold, int zero)
{
	int	count;

	count = 0;
	while (width - hold > 0)
	{
		if (zero)
			ft_putchar_pf('0');
		else
			ft_putchar_pf(' ');
		--width;
		++count;
	}
	return (count);
}
