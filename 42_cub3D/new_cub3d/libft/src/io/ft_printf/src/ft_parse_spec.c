/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_spec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 18:04:33 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 18:16:32 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

int	ft_spec_flag(char *s)
{
	if (!ft_strncmp("h", s, 1))
		return (1);
	if (!ft_strncmp("hh", s, 2))
		return (1);
	if (!ft_strncmp("l", s, 1))
		return (1);
	if (!ft_strncmp("ll", s, 2))
		return (1);
	return (0);
}

t_ll	type_d(va_list arg, t_flag flag)
{
	t_ll	v_i;

	if (flag.h)
		v_i = (short)va_arg(arg, int);
	else if (flag.hh)
		v_i = (char)va_arg(arg, int);
	else if (flag.l)
		v_i = (long)va_arg(arg, long);
	else if (flag.ll)
		v_i = va_arg(arg, t_ll);
	else
		v_i = va_arg(arg, int);
	return (v_i);
}

t_ull	type_u(va_list arg, t_flag flag)
{
	t_ull	v_ui;

	if (flag.h)
		v_ui = (t_ushort)va_arg(arg, t_uint);
	else if (flag.hh)
		v_ui = (t_uchar)va_arg(arg, t_uint);
	else if (flag.l)
		v_ui = (t_ul)va_arg(arg, t_ul);
	else if (flag.ll)
		v_ui = va_arg(arg, t_ull);
	else
		v_ui = va_arg(arg, t_uint);
	return (v_ui);
}
