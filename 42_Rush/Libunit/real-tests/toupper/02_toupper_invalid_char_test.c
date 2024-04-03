/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_toupper_invalid_char_test.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:50:53 by maddi             #+#    #+#             */
/*   Updated: 2022/01/09 21:07:32 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "real_tests.h"

int	toupper_invalid_char_test(void)
{
	if (ft_toupper(59) == 59)
		return (STATUS_SUCCESS);
	else
		return (STATUS_FAILURE);
}
