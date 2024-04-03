/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prog.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:41:59 by kaye              #+#    #+#             */
/*   Updated: 2021/12/12 14:33:01 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

t_hr	*sgt(void)
{
	static t_hr	*singleton = NULL;

	if (NULL == singleton)
	{
		singleton = ft_calloc(1, sizeof(t_hr));
		if (NULL == singleton)
			return (NULL);
	}
	return (singleton);
}
