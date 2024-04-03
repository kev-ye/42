/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iscntrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 22:23:56 by besellem          #+#    #+#             */
/*   Updated: 2021/04/24 23:02:37 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"

/*
** Check if between 0 and 31 or is equal to 127 in ascii chars
*/

int	ft_iscntrl(int c)
{
	return ((c >= 0 && c <= 037) || c == 0177);
}
