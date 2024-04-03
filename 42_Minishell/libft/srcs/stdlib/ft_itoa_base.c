/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 12:51:37 by besellem          #+#    #+#             */
/*   Updated: 2021/05/07 13:03:51 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_stdlib.h"

char	*ft_itoa_base(long long n, char *base)
{
	char		*data;
	long long	div;
	int			i;
	int			len;

	data = (char *)malloc(ft_nblen_base(n, ft_strlen(base)) + (n < 0) + 1);
	if (!data)
		return (NULL);
	i = -1;
	if (n < 0)
	{
		data[++i] = '-';
		n = -n;
	}
	len = ft_strlen(base);
	div = 1;
	while ((n / div) >= len)
		div *= len;
	while (div > 0)
	{
		data[++i] = base[n / div % len];
		div /= len;
	}
	data[++i] = '\0';
	return (data);
}
