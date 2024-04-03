/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_n.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 13:20:09 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 14:58:12 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

void	*n_spec(t_indicators *t, va_list ap)
{
	void	*n;

	if (t->hh)
		n = (char *)va_arg(ap, int *);
	else if (t->h)
		n = (short *)va_arg(ap, int *);
	else if (t->l)
		n = (long *)va_arg(ap, long *);
	else if (t->ll)
		n = (long long *)va_arg(ap, long long *);
	else
		n = (int *)va_arg(ap, int *);
	return (n);
}

void	ft_alloc_n(t_data **s, t_indicators t, va_list ap)
{
	int	size;
	int	*ptr;

	(void)t;
	size = 0;
	ptr = va_arg(ap, int *);
	ft_lstd_get_size(s, &size);
	*ptr = size;
}
