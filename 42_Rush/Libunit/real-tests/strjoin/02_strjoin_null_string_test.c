/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_strjoin_null_string_test.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 18:05:46 by maddi             #+#    #+#             */
/*   Updated: 2022/01/09 21:06:45 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "real_tests.h"

int	strjoin_null_string_test(void)
{
	if (ft_strjoin(NULL, "a") == NULL
		&& ft_strjoin("a", NULL) == NULL)
		return (STATUS_SUCCESS);
	else
		return (STATUS_FAILURE);
}
