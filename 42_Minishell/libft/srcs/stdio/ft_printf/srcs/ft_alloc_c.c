/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 19:37:44 by besellem          #+#    #+#             */
/*   Updated: 2021/05/19 15:12:05 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

void	ft_alloc_c(t_data **s, t_indicators t, va_list ap)
{
	char	data[2];
	char	*sp;

	data[0] = va_arg(ap, int);
	data[1] = '\0';
	sp = NULL;
	if ((t.dot >= 0 && t.zero >= 0) || t.width >= 0)
		sp = space_padding(ft_trns((*data), data, " "),
				ft_trni(t.width >= 0, t.width, t.zero));
	if (t.minus == -1)
		add_lstd(s, sp);
	ft_lstd_add(s, ft_lstd_new(data, 1));
	if (t.minus == 1)
		add_lstd(s, sp);
	ft_free(1, sp);
}
