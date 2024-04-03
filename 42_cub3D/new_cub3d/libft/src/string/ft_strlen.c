/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:58:41 by kaye              #+#    #+#             */
/*   Updated: 2021/03/09 19:47:45 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Computes the length of s.
*/

size_t	ft_strlen(const char *s)
{
	const char	*str;

	str = s;
	while (*str)
		++str;
	return (str - s);
}
