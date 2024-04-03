/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_strtrim_launcher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 21:25:55 by maddi             #+#    #+#             */
/*   Updated: 2022/01/09 21:55:17 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "real_tests.h"

int	strtrim_launcher(void)
{
	load_test("strtrim", "basic test", &strtrim_basic_test);
	load_test("strtrim", "set in str test", &strtrim_null_string_test);
	load_test("strtrim", "null string test", &strtrim_null_string_test);
	return (launch_tests());
}
