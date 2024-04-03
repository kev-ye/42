/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 19:25:38 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 18:16:09 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

int	ft_parse_char(int c, t_flag flag)
{
	int	count;

	count = 0;
	if (flag.minus)
		count += ft_putchar_pf(c);
	count += ft_parse_width(flag.width, 1, flag.zero);
	if (!flag.minus)
		count += ft_putchar_pf(c);
	return (count);
}
