/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 21:52:18 by kaye              #+#    #+#             */
/*   Updated: 2021/06/28 13:19:44 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

size_t	ft_strlen(const char *s)
{
	const char	*str;

	str = s;
	while (*str)
		++str;
	return (str - s);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
}

int	ft_atoi(const char *str)
{
	int	signe;
	int	res;

	signe = 1;
	res = 0;
	while (*str && ((*str >= '\t' && *str <= '\r') || (*str == ' ')))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe = -1;
		++str;
	}
	while (*str && *str >= 48 && *str <= 57)
	{
		res = res * 10 + *str - '0';
		++str;
	}
	return (res * signe);
}

void	ft_putnbr(int n)
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
	write(1, buffer + i, BUFFER_SIZE_PN - i);
}
