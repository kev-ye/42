/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_txt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 21:36:50 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 14:57:20 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

static int	len_alloc(const char *format)
{
	int	i;

	i = 0;
	while (format[i] && format[i] != '%')
		++i;
	return (i);
}

int	ft_alloc_txt(const char *format, t_data **s)
{
	char	*data;
	int		len;
	int		i;

	len = len_alloc(format);
	data = (char *)malloc(sizeof(char) * (len + 1));
	if (!data)
		return (-1);
	i = -1;
	while (++i < len)
		data[i] = format[i];
	data[i] = '\0';
	ft_lstd_add(s, ft_lstd_new(data, len));
	free(data);
	return (i);
}
