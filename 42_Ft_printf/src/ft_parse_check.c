/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 20:51:42 by kaye              #+#    #+#             */
/*   Updated: 2021/11/18 14:40:34 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_type(int type)
{
	const char	t[] = {
		'c',
		's',
		'p',
		'd',
		'i',
		'u',
		'x',
		'X',
		'%',
		'n',
		'o',
		'\0'
	};
	int			i;

	i = 0;
	while (t[i] != '\0')
	{
		if (type == t[i++])
			return (1);
	}
	return (0);
}

int	ft_flags(int flag)
{
	const char	f[] = {
		'-',
		'0',
		'.',
		'*',
		' ',
		'+',
		'#',
		'\0'
	};
	int			i;

	i = 0;
	while (f[i] != '\0')
	{
		if (flag == f[i++])
			return (1);
	}
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
