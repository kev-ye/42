/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_atoi_intmin_overflow_test.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:17:54 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 21:02:26 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	atoi_intmin_overflow_test(void)
{
	if ((long)atoi("-2147483649") == -2147483649)
		return (STATUS_SUCCESS);
	else
		return (STATUS_FAILURE);
}
