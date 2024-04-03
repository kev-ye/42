/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_strjoin_launcher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:58:51 by maddi             #+#    #+#             */
/*   Updated: 2022/01/09 21:06:58 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "real_tests.h"

int	strjoin_launcher(void)
{
	load_test("strjoin", "basic test", &strjoin_basic_test);
	load_test("strjoin", "null string test", &strjoin_null_string_test);
	load_test("strjoin", "empty string test", &strjoin_empty_string_test);
	return (launch_tests());
}
