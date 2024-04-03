/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 21:15:53 by kaye              #+#    #+#             */
/*   Updated: 2021/06/28 13:19:37 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	print_str(int opt)
{
	static int	c = 0;
	static int	i = 7;

	if (opt == SIGUSR1)
		c = c | (1 << i);
	if (i == 0)
	{
		ft_putchar(c);
		i = 8;
		c = 0;
	}
	--i;
}

static void	ft_handle(int code)
{
	if (code == SIGUSR1)
		print_str(SIGUSR1);
	else
		print_str(SIGUSR2);
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_putstr("PID : "B_CYAN);
	ft_putnbr(pid);
	ft_putstr("\n"NONE);
	signal(SIGUSR1, ft_handle);
	signal(SIGUSR2, ft_handle);
	while (1)
		pause();
	return (SUCCESS);
}
