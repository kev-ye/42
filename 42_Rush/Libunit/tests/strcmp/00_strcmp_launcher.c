/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_strcmp_launcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 16:55:04 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 20:17:05 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	strcmp_launcher(void)
{
	if (BONUS)
		print_header("strcmp");
	load_test("strcmp", "basic test", &strcmp_basic_test);
	load_test("strcmp", "null test", &strcmp_null_test);
	return (launch_tests());
}
