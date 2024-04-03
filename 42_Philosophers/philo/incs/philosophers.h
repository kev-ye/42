/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:20:00 by kaye              #+#    #+#             */
/*   Updated: 2021/07/15 19:57:56 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# if defined __linux__
#  include <stdint.h>
# endif

/* ASCII CODE */
# define B_BLACK "\033[1;30m"
# define B_RED "\033[1;31m"
# define B_GREEN "\033[1;32m"
# define B_YELLOW "\033[1;33m"
# define B_BLUE "\033[1;34m"
# define B_PURPLE "\033[1;35m"
# define B_CYAN "\033[1;36m"
# define NONE "\033[0m"
# define CLR "\033[2J\033[H"

/* MESSAGE */
# define ERROR_MSG "usage: \033[1;31m./philo [nbr_of_philo] [time_to_die]\n\
               [time_to_eat] [time_to_sleep]\n\
               \033[1;35m[[nbr_of_time_each_philo_must_eat]]\033[0m"
# define TIME_ERROR "Get time of day error\n"

/* RETURN */
# define FAILURE 1
# define SUCCESS 0
# define TO_FREE 1
# define NOTHING 0

/* ARGS */
# define ARGS_NBR 4

enum	e_args_index
{
	e_NP = 1,
	e_T2D = 2,
	e_T2E = 3,
	e_T2S = 4,
	e_ME = 5
};

/* PRINT STATES */
enum	e_eat_status
{
	e_PRINT_EAT,
	e_PRINT_FORK,
	e_PRINT_SLEEP,
	e_PRINT_THINK,
	e_PRINT_DIE
};

/* TIME2 */
enum	e_philo_status
{
	e_DIE,
	e_EAT,
	e_SLEEP,
	e_EATEN
};

/* STRUCT */
typedef struct s_philosophers
{
	pthread_t		philo;
	int				philo_i;
	int				nbr_eat;
	long long		last_meal;
}	t_philosophers;

typedef struct s_philo
{
	int				philo_nbr;
	int				must_eat;
	int				alive;
	int				die;
	int				time2[ARGS_NBR];
	long long		start;
	t_philosophers	*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex_common;
}	t_philo;

/* PHILOSOPHERS */
void		*philo(void *args);

// /* MONITOR */
int			still_alive(int index);
int			enough_ate(void);

/* MINI LIB */
int			ft_isdigit(int c);
int			ft_strdigit(const char *s);
long		ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);

/* UTILS */
int			__ret__(char *msg, int ret, int to_free);
t_philo		*singleton(void);
int			init_value(char **av);
void		do_sleep(long long ms, int index);
long long	get_time(void);
void		print_states(long long start, int index, int s_index, int is_die);
#endif