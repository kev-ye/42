/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:52:34 by kaye              #+#    #+#             */
/*   Updated: 2021/12/12 14:29:11 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void	free_clean(void **to_free)
{
	if (NULL != to_free && NULL != *to_free)
		free(*to_free);
	*to_free = NULL;
}

static void	clean_data(t_map *data_to_free)
{
	t_map	*to_free;

	while (NULL != data_to_free)
	{
		to_free = data_to_free;
		data_to_free = data_to_free->next;
		free_clean((void **)&to_free);
	}
}

void	clean(void)
{
	t_hr	*ptr;
	size_t	i;

	ptr = sgt();
	i = 0;
	if (NULL != ptr)
	{
		while (i < HASH_MAX)
		{
			if (NULL != ptr->hash_map[i])
				clean_data(ptr->hash_map[i]);
			++i;
		}
		if (NULL != ptr->buff)
			free_clean((void **)&ptr->buff);
		free_clean((void **)&ptr);
	}
}
