/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 20:44:42 by kaye              #+#    #+#             */
/*   Updated: 2021/07/18 13:25:37 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	still_alive(int index)
{
	singleton()->alive = singleton()->die;
	if (singleton()->alive >= singleton()->philo_nbr)
		return (0);
	if (singleton()->philo[index].last_meal != 0
		&& get_time() - singleton()->philo[index].last_meal
		> singleton()->time2[e_DIE])
	{
		print_states(singleton()->philo[index].last_meal,
			index, e_PRINT_DIE);
		sem_wait(singleton()->sem_print);
		singleton()->die = singleton()->philo_nbr;
		return (0);
	}
	return (1);
}

void	*monitoring_eat(void *args)
{
	int	i;

	(void)args;
	i = 0;
	while (i < singleton()->philo_nbr)
	{
		sem_wait(singleton()->sem_counter);
		++i;
	}
	sem_post(singleton()->sem_kill);
	sem_post(singleton()->sem_print);
	return (NULL);
}
