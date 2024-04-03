/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trnu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 22:24:53 by besellem          #+#    #+#             */
/*   Updated: 2021/04/26 22:31:07 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

uint32_t	ft_trnu(int condition, uint32_t if_true, uint32_t if_false)
{
	if (condition)
		return (if_true);
	else
		return (if_false);
}

size_t	ft_trnul(int condition, size_t if_true, size_t if_false)
{
	if (condition)
		return (if_true);
	else
		return (if_false);
}

uint64_t	ft_trnull(int condition, uint64_t if_true, uint64_t if_false)
{
	if (condition)
		return (if_true);
	else
		return (if_false);
}
