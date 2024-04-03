/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:58:47 by kaye              #+#    #+#             */
/*   Updated: 2021/03/11 20:46:25 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Compares not more than n characters.
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && (*s1 == *s2) && --n)
	{
		++s1;
		++s2;
	}
	if (n)
		return (((unsigned char) *s1) - ((unsigned char) *s2));
	return (0);
}
