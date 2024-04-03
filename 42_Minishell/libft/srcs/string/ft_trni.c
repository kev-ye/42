/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trni.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 22:23:46 by besellem          #+#    #+#             */
/*   Updated: 2021/04/26 22:28:37 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

int32_t	ft_trni(int condition, int32_t if_true, int32_t if_false)
{
	if (condition)
		return (if_true);
	else
		return (if_false);
}

ssize_t	ft_trnl(int condition, ssize_t if_true, ssize_t if_false)
{
	if (condition)
		return (if_true);
	else
		return (if_false);
}

int64_t	ft_trnll(int condition, int64_t if_true, int64_t if_false)
{
	if (condition)
		return (if_true);
	else
		return (if_false);
}
