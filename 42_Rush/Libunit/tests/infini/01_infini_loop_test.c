/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_infini_loop_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:15:47 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 21:02:33 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	infini_loop_test(void)
{
	if (loop_infini() == 1)
		return (STATUS_SUCCESS);
	else
		return (STATUS_FAILURE);
}
