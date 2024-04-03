/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_atoi_divise_by_zero_test.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 19:49:33 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 21:03:11 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	atoi_divise_by_zero_test(void)
{
	int	zero;

	zero = 0;
	if (atoi("42") / zero == 0)
		return (STATUS_SUCCESS);
	else
		return (STATUS_FAILURE);
}
