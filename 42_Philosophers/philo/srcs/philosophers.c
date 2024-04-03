/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:48:15 by kaye              #+#    #+#             */
/*   Updated: 2021/07/15 19:57:24 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_fork(int index, long long start)
{
	const int	left = index;
	const int	right = (index + 1) % singleton()->philo_nbr;

	if (index % 2 == 0)
	{
		if (singleton()->philo_nbr != 1)
		{
			pthread_mutex_lock(&singleton()->fork[right]);
			print_states(start, index, e_PRINT_FORK, 0);
		}
		pthread_mutex_lock(&singleton()->fork[left]);
		print_states(start, index, e_PRINT_FORK, 0);
	}
	else
	{
		pthread_mutex_lock(&singleton()->fork[left]);
		print_states(start, index, e_PRINT_FORK, 0);
		pthread_mutex_lock(&singleton()->fork[right]);
		print_states(start, index, e_PRINT_FORK, 0);
	}
}

static void	drop_fork(int index)
{
	const int	left = index;
	const int	right = (index + 1) % singleton()->philo_nbr;

	if (index % 2 == 0)
	{
		pthread_mutex_unlock(&singleton()->fork[left]);
		pthread_mutex_unlock(&singleton()->fork[right]);
	}
	else
	{
		pthread_mutex_unlock(&singleton()->fork[right]);
		pthread_mutex_unlock(&singleton()->fork[left]);
	}
}

static void	eating(int index, long long start)
{
	if (singleton()->philo_nbr != 1)
		print_states(start, index, e_PRINT_EAT, 0);
	singleton()->philo[index].last_meal = get_time();
	if (singleton()->philo_nbr == 1)
		do_sleep(singleton()->time2[e_DIE], index);
	else
		do_sleep(singleton()->time2[e_EAT], index);
	++singleton()->philo[index].nbr_eat;
}

static void	sleeping(int index, long long start)
{
	if (singleton()->philo_nbr != 1)
		print_states(start, index, e_PRINT_SLEEP, 0);
	do_sleep(singleton()->time2[e_SLEEP], index);
}

void	*philo(void *args)
{
	const int	i = (int)args;

	while (still_alive(i) && !enough_ate())
	{
		take_fork(i, singleton()->start);
		eating(i, singleton()->start);
		drop_fork(i);
		sleeping(i, singleton()->start);
		if (singleton()->philo_nbr != 1)
			print_states(singleton()->start, i, e_PRINT_THINK, 0);
		do_sleep(singleton()->time2[e_EAT] - singleton()->time2[e_SLEEP], i);
	}
	return (NULL);
}
