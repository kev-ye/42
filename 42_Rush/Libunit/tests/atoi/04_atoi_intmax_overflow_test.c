/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_atoi_intmax_overflow_test.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:14:37 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 21:02:17 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	atoi_intmax_overflow_test(void)
{
	if ((long)atoi("2147483648") == 2147483648)
		return (STATUS_SUCCESS);
	else
		return (STATUS_FAILURE);
}
