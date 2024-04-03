/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_common.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 01:11:34 by besellem          #+#    #+#             */
/*   Updated: 2021/05/19 15:15:20 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

char	*ft_mcat(char *dst, char *src)
{
	char	*new;
	size_t	len;

	len = ft_trnul((dst != NULL), ft_strlen(dst), 0);
	len += ft_trnul((src != NULL), ft_strlen(src), 0);
	new = (char *)ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	if (dst)
		ft_strcat(new, dst);
	if (src)
		ft_strcat(new, src);
	ft_free(2, dst, src);
	return (new);
}

int	ft_len_base(long long n, int base)
{
	long long	i;
	int			len;

	n = ft_trnll((n < 0), -n, n);
	len = 1;
	i = base;
	while (n / i > 0)
	{
		i *= base;
		++len;
	}
	return (len);
}

int	ft_ulen_base(unsigned long long n, int base)
{
	int	len;

	len = 1;
	while (n / base > 0)
	{
		n /= base;
		++len;
	}
	return (len);
}

char	*convert_base(long long n, char *base)
{
	const int	b_len = ft_strlen(base);
	char		*data;
	long long	div;
	int			i;

	data = (char *)malloc(sizeof(char) * ft_len_base(n, b_len) + (n < 0) + 1);
	if (!data)
		return (NULL);
	i = -1;
	if (n < 0)
	{
		n = -n;
		data[++i] = '-';
	}
	div = 1;
	while (n / div >= b_len)
		div *= b_len;
	while (div > 0)
	{
		data[++i] = base[n / div % b_len];
		div /= b_len;
	}
	data[++i] = '\0';
	return (data);
}

char	*convert_base_u(t_ull n, char *base)
{
	char	*data;
	t_ull	div;
	t_ull	len;
	int		i;

	len = ft_ulen_base(n, ft_strlen(base));
	data = (char *)malloc(sizeof(char) * (len + 1));
	if (!data)
		return (NULL);
	len = ft_strlen(base);
	div = 1;
	while (n / div >= len)
		div *= len;
	i = -1;
	while (div > 0)
	{
		data[++i] = base[n / div % len];
		div /= len;
	}
	data[++i] = '\0';
	return (data);
}
