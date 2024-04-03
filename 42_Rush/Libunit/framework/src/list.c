/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 19:09:06 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 21:36:07 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

static t_test	*create_new_test(
	char const *func_name,
	char const *test_name,
	int (*func)(void))
{
	t_test	*new_test;

	new_test = unit_calloc(1, sizeof(t_test));
	if (NULL == new_test)
		exit(STATUS_FAILURE);
	new_test->func_name = func_name;
	new_test->test_name = test_name;
	new_test->func = func;
	return (new_test);
}

void	load_test(
	char const *func_name,
	char const *test_name,
	int (*func)(void))
{
	t_unit	*ptr;
	t_test	*new_test;
	t_test	*tmp;

	new_test = create_new_test(func_name, test_name, func);
	ptr = unit_singleton(FALSE);
	if (NULL == ptr->test)
	{
		ptr->test = new_test;
		return ;
	}
	tmp = ptr->test;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new_test;
}

void	clean_tests(void)
{
	t_unit	*ptr;
	t_test	*tmp;
	t_test	*to_free;

	ptr = unit_singleton(FALSE);
	tmp = ptr->test;
	while (tmp)
	{
		to_free = tmp;
		tmp = tmp->next;
		free(to_free);
		to_free = NULL;
	}
	ptr->test = NULL;
}
