/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 20:44:42 by kaye              #+#    #+#             */
/*   Updated: 2021/07/15 19:56:43 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	still_alive(int index)
{
	pthread_mutex_lock(&singleton()->mutex_common);
	singleton()->alive = singleton()->die;
	if (singleton()->alive >= singleton()->philo_nbr)
	{
		pthread_mutex_unlock(&singleton()->mutex_common);
		return (0);
	}
	pthread_mutex_unlock(&singleton()->mutex_common);
	if (singleton()->philo[index].last_meal != 0
		&& get_time() - singleton()->philo[index].last_meal
		> singleton()->time2[e_DIE])
	{
		pthread_mutex_lock(&singleton()->mutex_common);
		print_states(singleton()->philo[index].last_meal,
			index, e_PRINT_DIE, 1);
		singleton()->die = singleton()->philo_nbr;
		pthread_mutex_unlock(&singleton()->mutex_common);
		return (0);
	}
	return (1);
}

int	enough_ate(void)
{
	int	index;
	int	count;

	if (singleton()->must_eat == 0)
		return (0);
	index = 0;
	count = 0;
	while (index < singleton()->philo_nbr)
	{
		pthread_mutex_lock(&singleton()->mutex_common);
		if (singleton()->philo[index].nbr_eat >= singleton()->must_eat)
		{
			pthread_mutex_unlock(&singleton()->mutex_common);
			++count;
		}
		else
			pthread_mutex_unlock(&singleton()->mutex_common);
		++index;
	}
	return (count == singleton()->philo_nbr);
}
