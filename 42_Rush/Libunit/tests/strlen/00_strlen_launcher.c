/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_strlen_launcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:15:47 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 20:17:38 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	strlen_launcher(void)
{
	if (BONUS)
		print_header("strlen");
	load_test("strlen", "basic test", &strlen_basic_test);
	load_test("strlen", "null test", &strlen_null_test);
	return (launch_tests());
}
