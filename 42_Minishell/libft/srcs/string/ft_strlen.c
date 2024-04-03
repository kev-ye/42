/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 02:29:36 by besellem          #+#    #+#             */
/*   Updated: 2021/05/09 21:33:09 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "defs.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (LIBC_NO_CRASH_ON_NULL && !s)
		return (0);
	i = 0;
	while (s[i])
		++i;
	return (i);
}
