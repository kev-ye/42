/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_strtrim_null_string_test.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 21:43:21 by maddi             #+#    #+#             */
/*   Updated: 2022/01/09 21:55:33 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "real_tests.h"

int	strtrim_null_string_test(void)
{
	if (ft_strtrim(NULL, "ba") == NULL)
		return (STATUS_SUCCESS);
	else
		return (STATUS_FAILURE);
}
