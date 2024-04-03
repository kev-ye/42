/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trn.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:29:56 by besellem          #+#    #+#             */
/*   Updated: 2021/04/26 22:32:07 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	*ft_trn(int condition, void *if_true, void *if_false)
{
	if (condition)
		return (if_true);
	else
		return (if_false);
}

char	*ft_trns(int condition, char *if_true, char *if_false)
{
	if (condition)
		return (if_true);
	else
		return (if_false);
}

double	ft_trnd(int condition, double if_true, double if_false)
{
	if (condition)
		return (if_true);
	else
		return (if_false);
}

long double	ft_trnld(int condition, long double if_true, long double if_false)
{
	if (condition)
		return (if_true);
	else
		return (if_false);
}
