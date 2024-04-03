/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_checks2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 23:03:38 by besellem          #+#    #+#             */
/*   Updated: 2020/11/27 14:53:14 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

int	check_htag(t_indicators *table)
{
	table->htag = 1;
	return (1);
}

int	check_spce(t_indicators *table)
{
	table->space = 1;
	if (table->plus == 1)
		table->space = 0;
	return (1);
}

int	check_plus(t_indicators *table)
{
	table->plus = 1;
	return (1);
}
