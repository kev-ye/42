/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_atoi_launcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:12:25 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 20:15:41 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	atoi_launcher(void)
{
	if (BONUS)
		print_header("atoi");
	load_test("atoi", "basic test", &atoi_basic_test);
	load_test("atoi", "inmax test", &atoi_intmax_test);
	load_test("atoi", "inmin test", &atoi_intmin_test);
	load_test("atoi", "inmax overflow test", &atoi_intmax_overflow_test);
	load_test("atoi", "inmin overflow test", &atoi_intmin_overflow_test);
	if (BONUS)
		load_test("atoi", "inmin overflow test", &atoi_divise_by_zero_test);
	return (launch_tests());
}
