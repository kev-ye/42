/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 02:29:33 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 11:48:28 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	res;
	size_t	i;
	size_t	j;

	i = ft_strlen(dst);
	if (dstsize == 0)
		return (ft_strlen(src));
	else if (dstsize > i)
		res = ft_strlen(src) + i;
	else
		res = ft_strlen(src) + dstsize;
	j = 0;
	while (src[j] && (i + j) < (dstsize - 1))
	{
		dst[i + j] = src[j];
		++j;
	}
	dst[i + j] = '\0';
	return (res);
}
