/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 12:56:34 by kaye              #+#    #+#             */
/*   Updated: 2021/02/05 09:30:14 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Compute the length of s, but never scans beyond the first maxlen bytes of s.
*/

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	const char *str;

	str = s;
	while (*str && maxlen--)
		++str;
	return (str - s);
}
