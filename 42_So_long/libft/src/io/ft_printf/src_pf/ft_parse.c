/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 19:27:15 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 18:16:39 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

int	ft_parse_flags(const char *format, int count, t_flag *flag, va_list arg)
{
	while (format[count])
	{
		if (!ft_flags_check(format, count))
			break ;
		if (format[count] == '0' && flag->minus == 0 && flag->width == 0)
			flag->zero = 1;
		if (format[count] == '.')
			count = ft_prec(format, ++count, flag, arg);
		if (format[count] == '-')
			*flag = ft_minus(*flag);
		if (format[count] == '*')
			*flag = ft_width(*flag, arg);
		if (ft_isdigit(format[count]))
			*flag = ft_digit(format[count], *flag);
		ft_parse_flags_plus(format, count, &flag);
		if (ft_type(format[count]))
		{
			flag->type = format[count];
			break ;
		}
		++count;
	}
	return (count);
}

void	ft_parse_flags_plus(const char *format, int count, t_flag **flag)
{
	if (format[count] == ' ')
		**flag = ft_space(**flag);
	if (format[count] == '+')
		**flag = ft_plus(**flag);
	if (format[count] == '#')
		**flag = ft_hashtag(**flag);
	if (!ft_strncmp("h", format + count, 1))
		**flag = ft_type_def(**flag, TYPE_H);
	if (!ft_strncmp("hh", format + count, 2))
		**flag = ft_type_def(**flag, TYPE_HH);
	if (!ft_strncmp("l", format + count, 1))
		**flag = ft_type_def(**flag, TYPE_L);
	if (!ft_strncmp("ll", format + count, 2))
		**flag = ft_type_def(**flag, TYPE_LL);
}

int	ft_parse_c_with_spec(va_list arg, t_flag flag)
{
	int	count;

	count = 0;
	count = ft_parse_char(va_arg(arg, int), flag);
	return (count);
}

int	ft_parse_s_with_spec(va_list arg, t_flag flag)
{
	int	count;

	count = 0;
	count = ft_parse_string(va_arg(arg, char *), flag);
	return (count);
}

int	ft_parse(int cnt, int type, va_list arg, t_flag flag)
{
	int	count;

	count = 0;
	if (type == 'c')
		count = ft_parse_c_with_spec(arg, flag);
	else if (type == 's')
		count = ft_parse_s_with_spec(arg, flag);
	else if (type == 'p')
		count = ft_parse_pointer(va_arg(arg, void *), flag);
	else if (type == 'd' || type == 'i')
		count = ft_parse_int(type_d(arg, flag), flag);
	else if (type == 'u')
		count = ft_parse_uint(type_u(arg, flag), flag);
	else if (type == 'x')
		count = ft_parse_hex(type_u(arg, flag), N_LOW, flag);
	else if (type == 'X')
		count = ft_parse_hex(type_u(arg, flag), N_UP, flag);
	else if (type == '%')
		count = ft_parse_char('%', flag);
	else if (type == 'n')
		count = ft_parse_int_p(va_arg(arg, int *), cnt);
	else if (type == 'o')
		count = ft_parse_octal(type_u(arg, flag), flag);
	return (count);
}
