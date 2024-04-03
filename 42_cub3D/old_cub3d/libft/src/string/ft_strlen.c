/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:58:41 by kaye              #+#    #+#             */
/*   Updated: 2021/02/05 09:30:09 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Computes the length of s.
*/

size_t		ft_strlen(const char *s)
{
	const char *str;

	str = s;
	while (*str)
		++str;
	return (str - s);
}
