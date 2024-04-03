/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_strlen_null_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:13:39 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 21:03:02 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	strlen_null_test(void)
{
	if (ft_strlen(NULL) == 0)
		return (STATUS_SUCCESS);
	else
		return (STATUS_FAILURE);
}
