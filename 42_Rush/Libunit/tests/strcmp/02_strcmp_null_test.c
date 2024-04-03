/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_strcmp_null_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 16:57:39 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 21:02:39 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	strcmp_null_test(void)
{
	if (ft_strcmp(NULL, NULL) == 0)
		return (STATUS_SUCCESS);
	else
		return (STATUS_FAILURE);
}
