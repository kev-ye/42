/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_strcpy_basic_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:52:26 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 21:02:53 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	strcpy_basic_test(void)
{
	char	buffer[6];
	char	*cpy;

	cpy = ft_strcpy(buffer, "hello");
	if (ft_strcmp(cpy, "hello") == 0)
		return (STATUS_SUCCESS);
	else
		return (STATUS_FAILURE);
}
