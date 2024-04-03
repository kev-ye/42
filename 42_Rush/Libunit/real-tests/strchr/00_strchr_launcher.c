/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_strchr_launcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 18:15:54 by maddi             #+#    #+#             */
/*   Updated: 2022/01/09 21:06:07 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "real_tests.h"

int	strchr_launcher(void)
{
	load_test("strchr", "basic test", &strchr_basic_test);
	return (launch_tests());
}
