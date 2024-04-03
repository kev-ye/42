/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 02:29:29 by besellem          #+#    #+#             */
/*   Updated: 2021/05/09 21:33:01 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "defs.h"

char	*ft_strdup(const char *s1)
{
	const size_t	_sz = ft_strlen(s1) + 1;
	char			*cpy;

	if (LIBC_NO_CRASH_ON_NULL && !s1)
		return (NULL);
	cpy = (char *)malloc(sizeof(char) * _sz);
	if (!cpy)
		return (NULL);
	return (ft_memcpy(cpy, s1, _sz));
}
