/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 11:51:03 by besellem          #+#    #+#             */
/*   Updated: 2021/05/19 15:23:17 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

int	check_min(t_indicators *table)
{
	table->minus = 1;
	return (0);
}

int	check_wdt(const char *format, va_list ap, t_indicators *table)
{
	if (*format && *format == '*')
	{
		table->width = va_arg(ap, int);
		if (table->width < 0)
		{
			table->minus = 1;
			table->width *= -1;
		}
		return (1);
	}
	else
		table->width = ft_atoi(format);
	return (ft_len_base(table->width, 10));
}

/*
** Maybe reinit `table->zero` in this case :
**
** if (table->minus == 1)
** 		return ;
*/

int	check_zero(const char *format, va_list ap, t_indicators *table)
{
	if (*format && *format == '0')
		return (0);
	if (*format && *format == '+')
		return (check_plus(table) - 1);
	if (*format && *format == '*')
	{
		table->zero = va_arg(ap, int);
		if (table->zero < 0)
		{
			table->width = -table->zero;
			table->zero = -1;
			table->minus = 1;
		}
		return (1);
	}
	if (*format && ft_atoi(format) < 0)
		return (check_min(table));
	else if (*format && ft_atoi(format) == 0)
	{
		table->zero = 0;
		return (0);
	}
	table->zero = ft_atoi(format);
	return (ft_len_base(table->zero, 10));
}

int	check_prec(const char *format, va_list ap, t_indicators *table)
{
	int	i;

	table->dot = 0;
	if (*format && *format == '*')
	{
		table->dot = va_arg(ap, int);
		if (table->dot < 0)
			table->dot = -1;
		return (1);
	}
	else
	{
		i = 0;
		if (*format && *format == '0')
			while (format[i] == '0')
				++i;
		if (ft_atoi(format + i) == 0)
			return (i);
		table->dot = ft_trni(ft_atoi(format + i) < 0, -1, ft_atoi(format + i));
		return (i + ft_len_base(table->dot, 10));
	}
}
