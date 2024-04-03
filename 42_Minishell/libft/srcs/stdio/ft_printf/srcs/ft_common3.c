/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_common3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 22:16:14 by besellem          #+#    #+#             */
/*   Updated: 2021/05/19 22:15:26 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

char	*space_padding(char *data, int padding)
{
	char	*spaces;
	int		data_len;
	int		len;

	if (padding <= 0)
		return (NULL);
	data_len = ft_trnul((data != NULL), ft_strlen(data), 0);
	len = ft_trni((data_len > padding), 0, padding - data_len);
	spaces = ft_malloc_c(ft_trni((len < 0), 0, len), ' ');
	return (spaces);
}

char	*convert_to_float(long long n, int sign)
{
	char		*data;
	long long	div;
	int			i;
	int			len;

	len = ft_len_base(n, 10) + 1;
	data = (char *)malloc(sizeof(char) * len);
	if (!data)
		return (NULL);
	i = -1;
	if (sign == 1)
		n = -n;
	div = 1;
	while (n / div >= 10)
		div *= 10;
	while (div > 0)
	{
		data[++i] = (n / div) % 10 + 48;
		div /= 10;
	}
	data[++i] = '\0';
	return (data);
}
