/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:54:11 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 18:40:10 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_intlen_base(int n, int base)
{
	size_t	count;

	if (n)
		count = 0;
	else
		count = 1;
	while (n)
	{
		n = n / base;
		++count;
	}
	return (count);
}
