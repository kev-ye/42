/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 20:09:02 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 21:42:08 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

typedef struct s_info
{
	int		status;
	char	*status_msg;
}	t_info;

typedef struct s_sig
{
	int		sig;
	int		status;
}	t_sig;

#if BONUS

static const t_info	g_info[STATUS_MAX] = {
{STATUS_OK, ANSCII_GREEN"OK"ANSCII_CLEAR},
{STATUS_KO, ANSCII_RED"KO"ANSCII_CLEAR},
{STATUS_SIGSEGV, ANSCII_YELLOW"SEGV"ANSCII_CLEAR},
{STATUS_SIGBUS, ANSCII_YELLOW"BUS"ANSCII_CLEAR},
{STATUS_SIGABRT, ANSCII_YELLOW"ABRT"ANSCII_CLEAR},
{STATUS_SIGFPE, ANSCII_YELLOW"FPE"ANSCII_CLEAR},
{STATUS_SIGPIPE, ANSCII_YELLOW"PIPE"ANSCII_CLEAR},
{STATUS_SIGILL, ANSCII_YELLOW"ILL"ANSCII_CLEAR},
{STATUS_TIMEOUT, ANSCII_YELLOW"TIMEOUT"ANSCII_CLEAR}
};
#else

static const t_info	g_info[STATUS_MAX] = {
{STATUS_OK, "OK"},
{STATUS_KO, "KO"},
{STATUS_SIGSEGV, "SEGV"},
{STATUS_SIGBUS, "BUS"}
};
#endif

#if BONUS

static const t_sig	g_sig[STATUS_MAX] = {
{SIGSEGV, STATUS_SIGSEGV},
{SIGBUS, STATUS_SIGBUS},
{SIGABRT, STATUS_SIGABRT},
{SIGFPE, STATUS_SIGFPE},
{SIGPIPE, STATUS_SIGPIPE},
{SIGILL, STATUS_SIGILL},
{SIGALRM, STATUS_TIMEOUT}
};
#else

static const t_sig	g_sig[STATUS_MAX] = {
{SIGSEGV, STATUS_SIGSEGV},
{SIGBUS, STATUS_SIGBUS}
};
#endif

static void	handle_info(int status)
{
	t_unit	*ptr;
	int		i;

	i = 0;
	ptr = unit_singleton(FALSE);
	while (i < STATUS_MAX)
	{
		if (g_info[i].status == status)
		{
			if (status == STATUS_OK)
				++ptr->info.result_success;
			else
				++ptr->info.result_failure;
			if (BONUS)
				dprintf(STDOUT_FILENO, "[%s]\n", g_info[i].status_msg);
			else
			{
				unit_putstr_fd("[", STDOUT_FILENO);
				unit_putstr_fd(g_info[i].status_msg, STDOUT_FILENO);
				unit_putendl_fd("]", STDOUT_FILENO);
			}
			return ;
		}
		++i;
	}
}

static void	handle_status(int status)
{
	int	i;

	i = 0;
	if (WIFEXITED(status) != FALSE)
	{
		if (WEXITSTATUS(status) == 0)
			handle_info(STATUS_OK);
		else if (BONUS && WEXITSTATUS(status) == SIGALRM)
			handle_info(STATUS_TIMEOUT);
		else
			handle_info(STATUS_KO);
	}
	if (WIFSIGNALED(status) == TRUE)
	{
		while (i < SIG_MAX)
		{
			if (WTERMSIG(status) == g_sig[i].sig)
				handle_info(g_sig[i].status);
			++i;
		}
	}
}

static void	handle_exit(int signal)
{
	(void)signal;
	exit(SIGALRM);
}

static void	fork_test(t_test *curr_test)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		exit(STATUS_FAILURE);
	if (pid == 0)
	{
		if (BONUS)
		{
			signal(SIGALRM, handle_exit);
			alarm(3);
		}
		exit(curr_test->func());
	}
	else
		wait(&status);
	handle_status(status);
}

int	launch_tests(void)
{
	t_unit	*ptr;
	t_test	*tmp;
	int		ret;

	ptr = unit_singleton(FALSE);
	tmp = ptr->test;
	while (tmp)
	{
		print_info(tmp);
		fork_test(tmp);
		tmp = tmp->next;
	}
	if (ptr->info.result_failure > 0)
		ret = STATUS_FAILURE;
	else
		ret = STATUS_SUCCESS;
	print_result();
	unit_clean();
	if (BONUS)
		dprintf(STDOUT_FILENO, ANSCII_BLUE"==================="ANSCII_CLEAR"\n");
	return (ret);
}
