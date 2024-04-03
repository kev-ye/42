/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsnprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 22:13:14 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 14:43:06 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static void	fill_buffer(t_data **s, char **ret, size_t size)
{
	t_data	**tracer;
	size_t	len;

	tracer = s;
	len = size;
	while (*tracer)
	{
		if ((size_t)(*tracer)->size < len - 1)
			ft_strncat(*ret, (*tracer)->data, (*tracer)->size);
		else
		{
			ft_strncat(*ret, (*tracer)->data, len - 1);
			return ;
		}
		len -= (*tracer)->size;
		tracer = &(*tracer)->next;
	}
}

static int	vsnprintf_process(char *str, size_t s, const char *fmt, va_list ap)
{
	int		size;
	t_data	*data;

	size = 0;
	*str = '\0';
	data = ft_parse_format(fmt, ap);
	ft_lstd_get_size(&data, &size);
	if (s > 1)
		fill_buffer(&data, &str, s);
	ft_lstd_clear(&data);
	return (size);
}

int	ft_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	int	len;

	len = vsnprintf_process(str, size, format, ap);
	return (len);
}
