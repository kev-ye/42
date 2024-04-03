/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 12:40:58 by besellem          #+#    #+#             */
/*   Updated: 2021/05/09 21:33:11 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "defs.h"

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	i;

	if ((LIBC_NO_CRASH_ON_NULL && !s) || maxlen == 0)
		return (0);
	i = 0;
	while (s[i] && i < maxlen)
		++i;
	return (i);
}
