/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 20:51:42 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 18:16:12 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

int	ft_type(int type)
{
	if (type == 'c')
		return (1);
	else if (type == 's')
		return (1);
	else if (type == 'p')
		return (1);
	else if (type == 'd' || type == 'i')
		return (1);
	else if (type == 'u')
		return (1);
	else if (type == 'x')
		return (1);
	else if (type == 'X')
		return (1);
	else if (type == '%')
		return (1);
	else if (type == 'n')
		return (1);
	else if (type == 'o')
		return (1);
	return (0);
}

int	ft_flags(int flag)
{
	if (flag == '-')
		return (1);
	else if (flag == '0')
		return (1);
	else if (flag == '.')
		return (1);
	else if (flag == '*')
		return (1);
	else if (flag == ' ')
		return (1);
	else if (flag == '+')
		return (1);
	else if (flag == '#')
		return (1);
	return (0);
}

int	ft_flags_check(const char *format, int count)
{
	if (!ft_isdigit(format[count]) && !ft_type(format[count])
		&& !ft_flags(format[count]) && !ft_spec_flag((char *)(format + count)))
		return (0);
	if ((ft_isdigit(format[count]) || ft_flags(format[count])
			|| ft_spec_flag((char *)(format + count)))
			&& format[count + 1] == '\0')
		return (0);
	return (1);
}
