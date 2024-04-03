/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_strjoin_basic_test.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 18:02:50 by maddi             #+#    #+#             */
/*   Updated: 2022/01/09 21:07:08 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "real_tests.h"

int	strjoin_basic_test(void)
{
	char	*s;

	s = ft_strjoin("aaa", "bbb");
	if (ft_strcmp(s, "aaabbb") == 0)
	{
		free(s);
		return (STATUS_SUCCESS);
	}
	else
		return (STATUS_FAILURE);
}
