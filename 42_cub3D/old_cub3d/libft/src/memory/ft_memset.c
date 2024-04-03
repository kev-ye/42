/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:57:55 by kaye              #+#    #+#             */
/*   Updated: 2020/11/04 17:42:40 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Writes len of c to b.
*/

void	*ft_memset(void *b, int c, size_t len)
{
	while (len)
		((unsigned char*)b)[--len] = (unsigned char)c;
	return (b);
}
