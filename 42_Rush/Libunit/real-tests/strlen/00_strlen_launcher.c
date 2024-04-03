/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_strlen_launcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:15:47 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 20:54:49 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "real_tests.h"

int	strlen_launcher(void)
{
	load_test("strlen", "basic test", &strlen_basic_test);
	return (launch_tests());
}
