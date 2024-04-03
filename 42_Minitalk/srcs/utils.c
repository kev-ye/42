/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 12:13:45 by kaye              #+#    #+#             */
/*   Updated: 2021/06/28 13:17:35 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	load_bar(long long current, long long max)
{
	long long	bar_len;
	long long	i;

	bar_len = 30;
	i = -1;
	ft_putstr(S_CLRLINE);
	if ((current / max) * bar_len != (current / max) * 100)
		ft_putstr(B_CYAN"STRING DONE !"NONE);
	else
		ft_putstr(B_CYAN"Loading ... "NONE);
	while (++i < ((double)current / max) * bar_len)
		ft_putchar('|');
	while (i++ < bar_len)
		ft_putchar(' ');
	ft_putchar(' ');
	ft_putnbr(((double)current / max) * 100);
	ft_putchar('%');
	ft_putchar(' ');
}

char	*add_c2str(char const *s1, char c)
{
	size_t	len;
	char	*str;
	int		i;

	if (!s1)
		len = 1;
	else
		len = ft_strlen(s1) + 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
		*str++ = s1[i++];
	*str++ = c;
	*str = '\0';
	if (s1)
		free((char *)s1);
	return (str - len);
}
