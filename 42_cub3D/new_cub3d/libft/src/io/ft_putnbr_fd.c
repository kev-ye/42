/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:56:53 by kaye              #+#    #+#             */
/*   Updated: 2021/03/09 17:11:16 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Outputs the integer n to given file descriptor.
*/

void	ft_putnbr_fd(int n, int fd)
{
	char			buffer[BUFFER_SIZE_PN];
	unsigned int	nbr;
	size_t			i;

	if (n < 0)
		nbr = -n;
	else
		nbr = n;
	i = BUFFER_SIZE_PN;
	while (nbr || i == BUFFER_SIZE_PN)
	{
		buffer[--i] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (n < 0)
		buffer[--i] = '-';
	write(fd, buffer + i, BUFFER_SIZE_PN - i);
}
