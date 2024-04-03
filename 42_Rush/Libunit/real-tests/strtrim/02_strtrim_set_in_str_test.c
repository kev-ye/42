/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_strtrim_set_in_str_test.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 21:41:06 by maddi             #+#    #+#             */
/*   Updated: 2022/01/09 21:47:45 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "real_tests.h"

int	strtrim_set_in_str(void)
{
	char	*s;

	s = ft_strtrim("  a a  ", " ");
	if (ft_strcmp(s, "a a") == 0)
	{
		free(s);
		return (STATUS_SUCCESS);
	}
	else
		return (STATUS_FAILURE);
}
