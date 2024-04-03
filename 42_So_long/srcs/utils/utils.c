/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:19:39 by kaye              #+#    #+#             */
/*   Updated: 2021/07/06 15:11:37 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	__free__(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

int	__open__(char *path, const int flag)
{
	const int	fd = open(path, flag);

	if (!fd)
		__exit__(strerror(errno), NULL, NOTHING, FAILURE);
	return ((int)fd);
}

t_win	*singleton(void)
{
	static t_win	*philo = NULL;

	if (!philo)
	{
		philo = ft_calloc(sizeof(t_win), 1);
		if (!philo)
			exit(FAILURE);
	}
	return (philo);
}
