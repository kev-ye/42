/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_strchr_basic_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 18:19:24 by maddi             #+#    #+#             */
/*   Updated: 2022/01/09 21:06:12 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "real_tests.h"

int	strchr_basic_test(void)
{
	char	*str;

	str = "aaabaab";
	if (ft_strchr(str, 'b') == str + 3)
		return (STATUS_SUCCESS);
	else
		return (STATUS_FAILURE);
}
