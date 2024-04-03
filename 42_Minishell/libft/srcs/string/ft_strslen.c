/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strslen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 22:48:40 by besellem          #+#    #+#             */
/*   Updated: 2021/05/10 22:55:15 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "defs.h"

size_t	ft_strslen(char **s)
{
	size_t	i;

	if (LIBC_NO_CRASH_ON_NULL && (!s || !*s))
		return (0);
	i = 0;
	while (s[i])
		++i;
	return (i);
}
