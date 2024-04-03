/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_strtrim_basic_test.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 21:27:50 by maddi             #+#    #+#             */
/*   Updated: 2022/01/09 21:42:24 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "real_tests.h"

int	strtrim_basic_test(void)
{
	char	*s;

	s = ft_strtrim("  aa  ", " ");
	if (ft_strcmp(s, "aa") == 0)
	{
		free(s);
		return (STATUS_SUCCESS);
	}
	else
		return (STATUS_FAILURE);
}
