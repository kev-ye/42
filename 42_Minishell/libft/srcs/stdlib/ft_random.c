/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 10:52:44 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 14:39:29 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"

/*
** Custom random function using the /dev/urandom file
** to generate the number.
*/

#define __RAND_BUF__ 9

long	ft_random(void)
{
	int		rbyte;
	int		fd;
	long	buf[__RAND_BUF__ + 1];
	size_t	i;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (1);
	rbyte = 1;
	if (read(fd, buf, __RAND_BUF__) > 0)
	{
		buf[__RAND_BUF__] = '\0';
		i = 0;
		while (buf[i])
			rbyte *= buf[i++];
	}
	close(fd);
	return (rbyte);
}
