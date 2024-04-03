/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vasprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 20:42:18 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 14:43:38 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static char	*vasprintf_process(const char *format, va_list ap, int *size)
{
	char	*ret;
	t_data	*data;

	*size = 0;
	data = ft_parse_format(format, ap);
	ft_lstd_get_size(&data, size);
	ret = (char *)ft_calloc(*size + 1, sizeof(char));
	if (!ret)
	{
		*size = -1;
		ft_lstd_clear(&data);
		return (NULL);
	}
	ft_fill_ret(&data, &ret);
	ft_lstd_clear(&data);
	return (ret);
}

int	ft_vasprintf(char **ret, const char *format, va_list ap)
{
	int	size;

	*ret = vasprintf_process(format, ap, &size);
	return (size);
}
