/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:49:55 by kaye              #+#    #+#             */
/*   Updated: 2021/07/14 20:21:06 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_value(char **av)
{
	int	i;

	if (!singleton())
		return (FAILURE);
	singleton()->philo_nbr = ft_atoi(av[e_NP]);
	singleton()->philo = ft_calloc(sizeof(t_philosophers),
		singleton()->philo_nbr);
	if (!singleton()->philo)
		return (FAILURE);
	i = 0;
	while (i < singleton()->philo_nbr)
	{
		singleton()->philo[i].philo_i = i + 1;
		++i;
	}
	singleton()->fork = ft_calloc(sizeof(pthread_mutex_t),
		singleton()->philo_nbr);
	if (!singleton()->fork)
		return (FAILURE);
	singleton()->time2[e_DIE] = ft_atoi(av[e_T2D]);
	singleton()->time2[e_EAT] = ft_atoi(av[e_T2E]);
	singleton()->time2[e_SLEEP] = ft_atoi(av[e_T2S]);
	if (av[e_ME] && singleton()->philo_nbr != 1)
		singleton()->must_eat = ft_atoi(av[e_ME]);
	return (SUCCESS);
}

long long	get_time(void)
{
	struct timeval	t;
	long long		ms;

	if (gettimeofday(&t, NULL) == -1)
	{
		printf("Time error: %s: %d\n", __FILE__, __LINE__);
		return (-1);
	}
	ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (ms);
}
