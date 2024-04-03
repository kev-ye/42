/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:19:31 by kaye              #+#    #+#             */
/*   Updated: 2021/07/15 19:56:33 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define __MICRO_SEC__ 400

void	__free__(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

int	__ret__(char *msg, int ret, int to_free)
{
	if (msg)
		printf("%s\n", msg);
	if (TO_FREE == to_free)
	{
		if (singleton())
		{
			if (singleton()->philo)
				__free__((void **)(&singleton()->philo));
			if (singleton()->fork)
				__free__((void **)(&singleton()->fork));
		}
		free(singleton());
	}
	return (ret);
}

t_philo	*singleton(void)
{
	static t_philo	*philo = NULL;

	if (!philo)
	{
		philo = ft_calloc(sizeof(t_philo), 1);
		if (!philo)
			return (NULL);
	}
	return (philo);
}

void	do_sleep(long long ms, int index)
{
	const long long	start = get_time();

	while (get_time() - start < ms && still_alive(index))
		usleep(__MICRO_SEC__);
}

void	print_states(long long start, int index, int s_index, int is_die)
{
	const char		*states[] = {"is eating", "has taken a fork",
		"is sleeping", "is thinking", "died"};

	if (singleton()->die == singleton()->philo_nbr)
		return ;
	if (enough_ate())
		return ;
	if (singleton()->philo_nbr != 1 && is_die == 0)
		pthread_mutex_lock(&singleton()->mutex_common);
	printf("[%lld] [%u] [%s]\n",
		get_time() - start,
		singleton()->philo[index].philo_i,
		states[s_index]);
	if (singleton()->philo_nbr != 1 && is_die == 0)
		pthread_mutex_unlock(&singleton()->mutex_common);
}
