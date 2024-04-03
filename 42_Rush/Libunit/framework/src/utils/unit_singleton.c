/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_singleton.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 19:17:32 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 21:00:34 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

t_unit	*unit_singleton(BOOL free_flag)
{
	static t_unit	*singleton = NULL;

	if (NULL == singleton)
	{
		singleton = unit_calloc(1, sizeof(t_unit));
		if (NULL == singleton)
			exit(STATUS_FAILURE);
	}
	if (free_flag == TRUE)
	{
		free(singleton);
		singleton = NULL;
	}
	return (singleton);
}
