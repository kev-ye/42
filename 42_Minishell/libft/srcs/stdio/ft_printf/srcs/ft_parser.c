/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 16:13:26 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 14:48:19 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

t_data	*ft_parse_format(const char *format, va_list ap)
{
	t_data	*data;
	t_types	*t;
	size_t	i;
	int		check;

	data = NULL;
	t = ft_init_conversions();
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && ++i)
		{
			check = ft_alloc_format(format + i, ap, &data, t);
			if (check == -1)
			{
				ft_lstd_clear(&data);
				return (NULL);
			}
			i += check;
		}
		else
			i += ft_alloc_txt(format + i, &data);
	}
	free(t);
	return (data);
}

int	ft_process(const char *format, va_list ap, int fd)
{
	int		size;
	t_data	*data;

	size = 0;
	data = ft_parse_format(format, ap);
	ft_lstd_print(&data, &size, fd);
	ft_lstd_clear(&data);
	return (size);
}
