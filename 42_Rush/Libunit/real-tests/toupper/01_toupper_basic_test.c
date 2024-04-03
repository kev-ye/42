/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_toupper_basic_test.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:46:39 by maddi             #+#    #+#             */
/*   Updated: 2022/01/09 21:07:30 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "real_tests.h"

int	toupper_basic_test(void)
{
	if (ft_toupper('a') == 'A')
		return (STATUS_SUCCESS);
	else
		return (STATUS_FAILURE);
}
