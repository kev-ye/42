/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:11:16 by besellem          #+#    #+#             */
/*   Updated: 2021/06/24 15:56:01 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* rl_on_new_line() does not exist on macOS */
#if defined(__APPLE__) && defined(__MACH__)

void	ft_interrupt(int code)
{
	if (SIGQUIT == code)
	{
		ft_putstr_fd("exit\n", STDIN_FILENO);
		ft_free_exit(SUCCESS);
	}
	else if (SIGINT == code && EINTR == errno)
	{
		singleton()->lrv = LRV_GENERAL_ERROR;
		if (2 == singleton()->rl_lvl)
			ft_free_exit(EXEC_FAILURE);
		ft_putstr("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else
		ft_putstr("\n");
}

#else /* you're probably testing the project on Linux */

void	ft_interrupt(int code)
{
	if (SIGQUIT == code)
	{
		ft_putstr_fd("exit\n", STDIN_FILENO);
		ft_free_exit(SUCCESS);
	}
	else if (SIGINT == code && EINTR == errno)
	{
		set_lrv(2);
		if (2 == singleton()->rl_lvl)
		{
			unlink_all_tmp_fd(0);
			ft_free_exit(1);
		}
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

#endif
