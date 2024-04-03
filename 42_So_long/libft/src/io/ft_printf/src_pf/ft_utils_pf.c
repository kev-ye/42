/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:56:43 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 18:16:44 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

int	ft_putchar_pf(char c)
{
	write(1, &c, 1);
	return (1);
}

size_t	ft_putstr_pf(char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	write(1, s, len);
	return (len);
}

int	ft_putstr_prec_pf(char *s, int prec)
{
	int	count;

	count = 0;
	while (s[count] && count < prec)
		(void)ft_putchar_pf(s[count++]);
	return (count);
}
