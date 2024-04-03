/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 22:18:36 by besellem          #+#    #+#             */
/*   Updated: 2021/05/19 22:40:05 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

int	is_conversion(const char *s, t_types *t)
{
	int	i;

	i = -1;
	while (t[++i].type)
		if (*s == t[i].type)
			return (i);
	return (-1);
}

int	is_specifier(const char *format, t_indicators *t)
{
	if (t->is_specifier != 0)
		return (-1);
	t->is_specifier = 1;
	if (ft_strncmp("hh", format, 2) == 0)
		t->hh = 1;
	else if (ft_strncmp("h", format, 1) == 0)
		t->h = 1;
	else if (ft_strncmp("ll", format, 2) == 0)
		t->ll = 1;
	else if (ft_strncmp("l", format, 1) == 0)
		t->l = 1;
	else if (ft_strncmp("L", format, 1) == 0)
		t->lf = 1;
	else
		return (-1);
	return (0);
}

void	init_indicators(t_indicators *table)
{
	table->width = -1;
	table->minus = -1;
	table->zero = -1;
	table->dot = -1;
	table->htag = 0;
	table->space = 0;
	table->plus = 0;
	table->is_specifier = 0;
	table->h = 0;
	table->hh = 0;
	table->l = 0;
	table->ll = 0;
	table->lf = 0;
}

int	fill_indicators(const char *format, va_list ap, t_indicators *table)
{
	int	index;

	if (*format == '-')
		index = 1 + check_min(table);
	else if (*format == '0')
		index = 1 + check_zero(format + 1, ap, table);
	else if (*format == '*' || (*format >= '1' && *format <= '9'))
		index = check_wdt(format, ap, table);
	else if (*format == '.')
		index = 1 + check_prec(format + 1, ap, table);
	else if (*format == '#')
		index = check_htag(table);
	else if (*format == ' ')
		index = check_spce(table);
	else if (*format == '+')
		index = check_plus(table);
	else if (is_specifier(format, table) != -1)
		return (1 + (table->hh || table->ll || table->lf));
	else
		return (-1);
	return (index);
}

int	ft_alloc_format(const char *format, va_list ap, t_data **s, t_types *t)
{
	t_indicators	table;
	int				index;
	int				i;
	int				check;

	init_indicators(&table);
	i = 0;
	while (format[i])
	{
		index = is_conversion(format + i, t);
		if (index != -1)
			break ;
		check = fill_indicators(format + i, ap, &table);
		if (check == -1)
			return (-1);
		i += check;
	}
	if (!format[i])
		return (-1);
	t[index].f(s, table, ap);
	return (i + 1);
}
