/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_atoi_launcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:12:25 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 20:53:30 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "real_tests.h"

int	atoi_launcher(void)
{
	load_test("atoi", "basic test", &atoi_basic_test);
	load_test("atoi", "inmax test", &atoi_intmax_test);
	load_test("atoi", "inmin test", &atoi_intmin_test);
	return (launch_tests());
}
