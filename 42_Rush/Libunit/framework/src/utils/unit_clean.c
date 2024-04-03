/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:03:33 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 21:00:25 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

void	unit_clean(void)
{
	t_unit	*ptr;

	ptr = unit_singleton(FALSE);
	if (ptr)
	{
		clean_tests();
		unit_bzero(ptr, sizeof(t_unit));
		unit_singleton(TRUE);
	}
	ptr = NULL;
}
