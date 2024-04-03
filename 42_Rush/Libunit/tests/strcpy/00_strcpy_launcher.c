/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_strcpy_launcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:47:26 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 21:45:20 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	strcpy_launcher(void)
{
	if (BONUS)
		print_header("strcpy");
	load_test("strcpy", "basic test", &strcpy_basic_test);
	load_test("strcpy", "bus test", &strcpy_bus_test);
	if (BONUS)
		load_test("strcpy", "abort test", &strcpy_abrt_test);
	return (launch_tests());
}
