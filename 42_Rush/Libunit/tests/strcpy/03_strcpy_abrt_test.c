/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_strcpy_abrt_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 19:38:12 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 21:02:45 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	strcpy_abrt_test(void)
{
	char	buffer[1];
	char	*cpy;

	ft_strcpy(buffer, "hello");
	abort();
	if (ft_strcmp(cpy, "hello") == 0)
		return (STATUS_SUCCESS);
	else
		return (STATUS_FAILURE);
}
