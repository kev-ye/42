/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_flag_plus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 19:09:52 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 18:16:17 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

t_flag	ft_space(t_flag flag)
{
	if (!flag.plus)
		flag.space = 1;
	return (flag);
}

t_flag	ft_plus(t_flag flag)
{
	if (flag.space)
		flag.space = 0;
	flag.plus = 1;
	return (flag);
}

t_flag	ft_hashtag(t_flag flag)
{
	flag.hashtag = 1;
	return (flag);
}

t_flag	ft_type_def(t_flag flag, int type)
{
	if (type == TYPE_H)
		flag.h = 1;
	if (type == TYPE_HH)
		flag.hh = 1;
	if (type == TYPE_L)
		flag.l = 1;
	if (type == TYPE_LL)
		flag.ll = 1;
	return (flag);
}
