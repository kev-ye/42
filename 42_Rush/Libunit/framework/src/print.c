/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:36:38 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 20:59:41 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

void	print_info(t_test *curr_test)
{
	if (BONUS)
		dprintf(STDOUT_FILENO, ANSCII_CYAN"%s"ANSCII_CLEAR": %s: ",
			curr_test->func_name, curr_test->test_name);
	else
	{
		unit_putstr_fd(curr_test->func_name, STDOUT_FILENO);
		unit_putstr_fd(": ", STDOUT_FILENO);
		unit_putstr_fd(curr_test->test_name, STDOUT_FILENO);
		unit_putstr_fd(": ", STDOUT_FILENO);
	}
}

void	print_result(void)
{
	t_unit	*ptr;
	int		total;
	int		suc;

	ptr = unit_singleton(FALSE);
	unit_putendl_fd("", STDOUT_FILENO);
	suc = ptr->info.result_success;
	total = ptr->info.result_success + ptr->info.result_failure;
	if (BONUS)
		dprintf(STDOUT_FILENO,
			ANSCII_GREEN"%d"ANSCII_CLEAR" / %d tests checked\n", suc, total);
	else
	{
		unit_putnbr_fd(suc, STDOUT_FILENO);
		unit_putstr_fd(" / ", STDOUT_FILENO);
		unit_putnbr_fd(total, STDOUT_FILENO);
		unit_putendl_fd(" tests checked", STDOUT_FILENO);
	}
}

#if BONUS

void	print_header(char *name)
{
	dprintf(STDOUT_FILENO,
		ANSCII_BLUE">>>"ANSCII_CLEAR" ["ANSCII_BLUE"%s"ANSCII_CLEAR"]\n", name);
}

#endif