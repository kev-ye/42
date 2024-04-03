/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:19:31 by kaye              #+#    #+#             */
/*   Updated: 2021/07/16 18:11:20 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

#define __MICRO_SEC__ 400

t_philo	*singleton(void)
{
	static t_philo	*philo = NULL;

	if (!philo)
	{
		philo = ft_calloc(sizeof(t_philo), 1);
		if (!philo)
		{
			printf("Malloc error: %s: %d\n", __FILE__, __LINE__);
			__exit__(NULL, FAILURE, NOTHING, NOTHING);
		}
	}
	return (philo);
}

sem_t	*__sem_open__(const char *to_create, int flag, int priv, int lock)
{
	sem_t	*new_sem;

	sem_unlink(to_create);
	new_sem = sem_open(to_create, flag, priv, lock);
	if (new_sem == SEM_FAILED)
	{
		printf("Malloc error: %s: %d\n", __FILE__, __LINE__);
		__exit__(NULL, FAILURE, TO_FREE, TO_CLOSE);
	}
	return (new_sem);
}

void	do_sleep(long long ms, int index)
{
	const long long	start = get_time();

	while (get_time() - start < ms && still_alive(index))
		usleep(__MICRO_SEC__);
}

void	print_states(long long start, int index, int s_index)
{
	const char		*states[] = {"is eating", "has taken a fork",
		"is sleeping", "is thinking", "died"};

	if (singleton()->die == singleton()->philo_nbr)
		return ;
	if (s_index == e_PRINT_DIE)
		sem_wait(singleton()->sem_die);
	sem_wait(singleton()->sem_print);
	printf("[%lld] [%u] [%s]\n",
		get_time() - start,
		singleton()->philo[index].philo_i,
		states[s_index]);
	sem_post(singleton()->sem_print);
}
