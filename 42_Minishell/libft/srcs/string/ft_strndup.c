/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 18:20:21 by besellem          #+#    #+#             */
/*   Updated: 2021/05/09 21:33:13 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "defs.h"

char	*ft_strndup(const char *s1, size_t n)
{
	const size_t	_sz = ft_strnlen(s1, n);
	char			*cpy;

	if (LIBC_NO_CRASH_ON_NULL && !s1)
		return (NULL);
	cpy = (char *)malloc(sizeof(char) * (_sz + 1));
	if (!cpy)
		return (NULL);
	cpy[_sz] = '\0';
	return ((char *)ft_memcpy(cpy, s1, _sz));
}
