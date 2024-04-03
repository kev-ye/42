/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 13:58:36 by besellem          #+#    #+#             */
/*   Updated: 2021/05/09 21:47:59 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_stdlib.h"

static int	ft_len(size_t size, char **strs, char *sep)
{
	const size_t	sep_len = ft_strlen(sep);
	size_t			len;
	size_t			i;

	i = 0;
	len = 0;
	while (i < size)
	{
		len += ft_strlen(strs[i]);
		if ((i + 1) < size)
			len += sep_len;
		++i;
	}
	return (len);
}

char	*ft_strsjoin(size_t size, char **strs, char *sep)
{
	char	*s;
	size_t	i;

	if (!strs || !sep)
		return (NULL);
	s = (char *)ft_calloc(ft_len(size, strs, sep) + 1, sizeof(char));
	if (!s)
		return (NULL);
	if (size <= 0)
		return (s);
	i = 0;
	while (i < size)
	{
		ft_strcat(s, strs[i]);
		if ((i + 1) < size)
			ft_strcat(s, sep);
		++i;
	}
	return (s);
}
