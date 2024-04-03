/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 02:29:26 by besellem          #+#    #+#             */
/*   Updated: 2021/05/16 01:20:23 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#define __BYTE 8

static unsigned long	get_c_long_aligned(unsigned char c, size_t l_size)
{
	const unsigned long	c_ = (unsigned long)c;
	unsigned long		c_ret;

	c_ret = 0;
	while (l_size > 0)
	{
		--l_size;
		c_ret |= (c_ << (__BYTE * l_size));
	}
	return (c_ret);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			l_size;
	unsigned long	c_long_aligned;
	unsigned long	*l_ptr;
	unsigned char	*c_ptr;

	c = (unsigned char)c;
	l_size = sizeof(unsigned long);
	if (c == 0)
		c_long_aligned = 0;
	else
		c_long_aligned = get_c_long_aligned(c, l_size);
	l_ptr = (unsigned long *)b;
	while (len >= l_size)
	{
		*l_ptr++ = c_long_aligned;
		len -= l_size;
	}
	if (len > 0)
	{
		c_ptr = (unsigned char *)l_ptr;
		while (len--)
			*c_ptr++ = c;
	}
	return (b);
}
