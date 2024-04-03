/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_strjoin_empty_string_test.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 18:32:47 by maddi             #+#    #+#             */
/*   Updated: 2022/01/09 21:06:47 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "real_tests.h"

int	strjoin_empty_string_test(void)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin("", "a");
	s2 = ft_strjoin("a", "");
	if (ft_strcmp(s1, "a") == 0 && ft_strcmp(s2, "a") == 0)
	{
		free(s1);
		free(s2);
		return (STATUS_SUCCESS);
	}
	else
		return (STATUS_FAILURE);
}
