/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:14:40 by kaye              #+#    #+#             */
/*   Updated: 2021/07/16 18:07:32 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	__free__(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	__sem_unlink__(void)
{
	t_philo	*philo;

	philo = singleton();
	sem_unlink(S_FORK);
	sem_unlink(S_KILL);
	sem_unlink(S_DIE);
	sem_unlink(S_PRINT);
	sem_unlink(S_PMEC);
}

void	__sem_close__(void)
{
	t_philo	*philo;

	philo = singleton();
	if (philo->sem_fork && philo->sem_fork != SEM_FAILED)
		sem_close(philo->sem_fork);
	if (philo->sem_kill && philo->sem_kill != SEM_FAILED)
		sem_close(philo->sem_kill);
	if (philo->sem_die && philo->sem_die != SEM_FAILED)
		sem_close(philo->sem_die);
	if (philo->sem_print && philo->sem_print != SEM_FAILED)
		sem_close(philo->sem_print);
	if (philo->sem_counter && philo->sem_counter != SEM_FAILED)
		sem_close(philo->sem_counter);
}

void	kill_philo(void)
{
	int	i;

	i = 0;
	while (i < singleton()->philo_nbr)
	{
		kill(singleton()->philo[i++].pid, SIGKILL);
	}
}

int	__exit__(char *msg, int ret, int to_free, int to_close)
{
	if (msg)
		printf("%s\n", msg);
	if (TO_CLOSE == to_close)
	{
		if (singleton())
		{
			__sem_close__();
			__sem_unlink__();
		}
	}
	if (TO_FREE == to_free)
	{
		if (singleton())
		{
			kill_philo();
			if (singleton()->philo)
				__free__((void **)(&singleton()->philo));
		}
		memset(singleton(), 0, sizeof(t_philo));
		free(singleton());
	}
	exit(ret);
}
