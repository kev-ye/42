/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_conversions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 04:07:12 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 14:53:35 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

static void	add_conversion(t_types *t, char type, void (*f)())
{
	t->type = type;
	t->f = f;
}

static void	fill(t_types *t)
{
	add_conversion(&t[0], '%', &ft_alloc_mod);
	add_conversion(&t[1], 'c', &ft_alloc_c);
	add_conversion(&t[2], 's', &ft_alloc_s);
	add_conversion(&t[3], 'p', &ft_alloc_p);
	add_conversion(&t[4], 'd', &ft_alloc_d);
	add_conversion(&t[5], 'i', &ft_alloc_i);
	add_conversion(&t[6], 'u', &ft_alloc_u);
	add_conversion(&t[7], 'x', &ft_alloc_hex_min);
	add_conversion(&t[8], 'X', &ft_alloc_hex_maj);
	add_conversion(&t[9], 'f', &ft_alloc_f);
	add_conversion(&t[10], 'n', &ft_alloc_n);
	add_conversion(&t[11], 'o', &ft_alloc_o);
	add_conversion(&t[12], 'b', &ft_alloc_b);
}

t_types	*ft_init_conversions(void)
{
	t_types	*t;
	int		size;

	size = 13;
	t = (t_types *)malloc(sizeof(t_types) * (size + 1));
	if (!t)
		return (NULL);
	fill(t);
	t[size].type = '\0';
	return (t);
}
