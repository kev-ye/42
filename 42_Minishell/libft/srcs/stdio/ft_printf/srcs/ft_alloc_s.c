/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 21:06:02 by besellem          #+#    #+#             */
/*   Updated: 2021/05/19 15:42:41 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

void	ft_alloc_s(t_data **s, t_indicators t, va_list ap)
{
	char	*data;
	char	*sp;
	int		size;
	int		tmp;

	data = va_arg(ap, char *);
	data = ft_trns((data != NULL), data, "(null)");
	size = ft_strlen(data);
	sp = NULL;
	if (t.dot >= 0)
		size = ft_trni((size >= t.dot), t.dot, size);
	tmp = ft_strlen(data) + t.width - size;
	if ((t.dot >= 0 && t.zero >= 0) || t.width >= 0)
		sp = space_padding(data, tmp);
	if (t.minus == -1)
		add_lstd(s, sp);
	ft_lstd_add(s, ft_lstd_new(data, size));
	if (t.minus == 1)
		add_lstd(s, sp);
	ft_free(1, sp);
}
