/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:25:25 by kaye              #+#    #+#             */
/*   Updated: 2021/07/16 18:07:47 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	do_fork(void)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	while (i < singleton()->philo_nbr)
	{
		singleton()->philo[i].pid = fork();
		if (singleton()->philo[i].pid < 0)
		{
			printf("Fork error: %s: %d\n", __FILE__, __LINE__);
			__exit__(NULL, FAILURE, TO_FREE, TO_CLOSE);
		}
		else if (singleton()->philo[i].pid == 0)
			philo((void *)(intptr_t)i);
		++i;
	}
	pthread_create(&monitor, NULL, monitoring_eat, NULL);
	pthread_join(monitor, NULL);
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
		return (__exit__(ERROR_MSG, FAILURE, NOTHING, NOTHING));
	if (FAILURE == args_check(av))
		return (__exit__(ERROR_MSG, FAILURE, NOTHING, NOTHING));
	init_value(av);
	singleton()->start = get_time();
	if (singleton()->start == -1)
		__exit__(NULL, FAILURE, TO_FREE, TO_CLOSE);
	do_fork();
	sem_wait(singleton()->sem_kill);
	__exit__(NULL, SUCCESS, TO_FREE, TO_CLOSE);
	return (0);
}
