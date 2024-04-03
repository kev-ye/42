/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:25:25 by kaye              #+#    #+#             */
/*   Updated: 2021/07/14 20:21:27 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_phread(void)
{
	int	i;

	i = 0;
	while (i < singleton()->philo_nbr)
	{
		if (pthread_mutex_init(&singleton()->fork[i++], NULL) != 0)
			return (FAILURE);
	}
	if (pthread_mutex_init(&singleton()->mutex_common, NULL) != 0)
		return (FAILURE);
	i = 0;
	while (i < singleton()->philo_nbr)
	{
		if (pthread_create(&singleton()->philo[i].philo,
				NULL, philo, (void *)(intptr_t)i) != 0)
			return (FAILURE);
		++i;
	}
	return (SUCCESS);
}

static int	do_pthread(void)
{
	int	i;

	if (init_phread() != SUCCESS)
		return (FAILURE);
	i = 0;
	while (i < singleton()->philo_nbr)
	{
		if (pthread_join(singleton()->philo[i++].philo, NULL) != 0)
			return (FAILURE);
	}
	i = 0;
	while (i < singleton()->philo_nbr)
		pthread_mutex_destroy(&singleton()->fork[i++]);
	pthread_mutex_destroy(&singleton()->mutex_common);
	return (SUCCESS);
}

static int	args_check(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!ft_strdigit(av[i]))
			return (FAILURE);
		if (av[i][0] == '0' && av[i][1] == '\0')
			return (FAILURE);
		if (ft_atoi(av[i]) > INT32_MAX || ft_atoi(av[i]) < INT32_MIN)
			return (FAILURE);
		++i;
	}
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (__ret__(ERROR_MSG, FAILURE, NOTHING));
	if (FAILURE == args_check(av))
		return (__ret__(ERROR_MSG, FAILURE, NOTHING));
	if (init_value(av) == FAILURE)
	{
		printf("Malloc error: %s: %d\n", __FILE__, __LINE__);
		return (__ret__(NULL, FAILURE, TO_FREE));
	}
	singleton()->start = get_time();
	if (singleton()->start == -1)
		return (__ret__(NULL, FAILURE, TO_FREE));
	if (do_pthread() == FAILURE)
		return (__ret__(NULL, FAILURE, TO_FREE));
	return (__ret__(NULL, SUCCESS, TO_FREE));
}
