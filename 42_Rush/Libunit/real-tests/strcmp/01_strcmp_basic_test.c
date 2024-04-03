/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_strcmp_basic_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 16:56:59 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 21:06:24 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "real_tests.h"

int	strcmp_basic_test(void)
{
	if (ft_strcmp("hello", "hello") == 0)
		return (STATUS_SUCCESS);
	else
		return (STATUS_FAILURE);
}
