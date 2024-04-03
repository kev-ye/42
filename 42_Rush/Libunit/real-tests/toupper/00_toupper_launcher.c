/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_toupper_launcher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:44:12 by maddi             #+#    #+#             */
/*   Updated: 2022/01/09 21:07:28 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "real_tests.h"

int	toupper_launcher(void)
{
	load_test("toupper", "basic test", &toupper_basic_test);
	load_test("toupper", "invalid char test", &toupper_invalid_char_test);
	return (launch_tests());
}
