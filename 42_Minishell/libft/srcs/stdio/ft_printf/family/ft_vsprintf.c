/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 21:32:13 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 14:42:57 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static int	vsprintf_process(char *str, const char *fmt, va_list ap)
{
	int		size;
	t_data	*data;

	size = 0;
	*str = '\0';
	data = ft_parse_format(fmt, ap);
	ft_lstd_get_size(&data, &size);
	ft_fill_ret(&data, &str);
	ft_lstd_clear(&data);
	return (size);
}

int	ft_vsprintf(char *str, const char *format, va_list ap)
{
	int	size;

	size = vsprintf_process(str, format, ap);
	return (size);
}
