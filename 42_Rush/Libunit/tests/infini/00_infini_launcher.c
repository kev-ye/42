/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_infini_launcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:15:47 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 20:16:58 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	infini_launcher(void)
{
	if (BONUS)
		print_header("infini");
	load_test("infini", "infini loop test", &infini_loop_test);
	return (launch_tests());
}
