/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 22:33:29 by besellem          #+#    #+#             */
/*   Updated: 2021/06/24 18:35:31 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_spl_c
{
	pid_t	pid;
	int		status;
	int		lrv;
}	t_spl_c;

typedef struct s_ulk_tmp
{
	char	*old_name;
	char	*new_name;
	char	*fd_nbr;
	int		fd;
}	t_ulk_tmp;

static void	cmd_updating(t_list **lst_cmd, char **new, int i, int j)
{
	char	*tmp;

	tmp = NULL;
	while (TRUE)
	{
		while (((t_cmd *)(*lst_cmd)->content)->args[i][j]
			&& ((t_cmd *)(*lst_cmd)->content)->args[i][j] != -1)
			++j;
		if (((t_cmd *)(*lst_cmd)->content)->args[i][j] == '\0')
			break ;
		ft_asprintf(&(*new), "%.*s%d%s", j,
			((t_cmd *)(*lst_cmd)->content)->args[i],
			singleton()->lrv,
			((t_cmd *)(*lst_cmd)->content)->args[i] + j + 1);
		tmp = ((t_cmd *)(*lst_cmd)->content)->args[i];
		((t_cmd *)(*lst_cmd)->content)->args[i] = *new;
		ft_memdel((void **)&tmp);
		j += ft_nblen(singleton()->lrv);
	}
}

void	cmd_up(t_list *lst_cmd)
{
	int		i;
	int		j;
	char	*new;

	new = NULL;
	while (lst_cmd)
	{
		i = 0;
		while ((t_cmd *)lst_cmd->content
			&& ((t_cmd *)lst_cmd->content)->args
			&& ((t_cmd *)lst_cmd->content)->args[i])
		{
			j = 0;
			cmd_updating(&lst_cmd, &new, i, j);
			++i;
		}
		if (flag_check(lst_cmd) == FLG_EO_CMD)
			break ;
		lst_cmd = lst_cmd->next;
	}
}

void	simple_cmd(void *cmd)
{
	t_spl_c	spl_c;

	spl_c.status = 1;
	if (builtin_exec((t_cmd *)cmd) == NOT_FOUND)
	{
		spl_c.pid = fork();
		if (spl_c.pid < 0)
			exit(PID_FAILURE);
		else if (spl_c.pid == 0)
		{
			signal(SIGQUIT, ft_interrupt);
			spl_c.lrv = sys_exec(cmd);
			exit(spl_c.lrv);
		}
		else
			waitpid(spl_c.pid, &spl_c.status, 0);
		set_lrv(spl_c.status);
	}
}

void 	unlink_all_tmp_fd(int i)
{
	char	*new_name;
	int		fd;

	new_name = NULL;
	fd = -1;
	ft_asprintf(&new_name, "%s%d", TMP_FD, i);
	fd = open(new_name, O_RDWR);
	if (fd != -1)
	{
		close(fd);
		unlink(new_name);
		free(new_name);
		unlink_all_tmp_fd(++i);
	}
	else
	{
		ft_memdel((void **)&new_name);
		return ;
	}
}

void	ft_exec_each_cmd(t_list *lst_cmd)
{
	t_list	*tmp;
	int		cmd_line;
	int		i;

	tmp = lst_cmd;
	cmd_line = -1;
	i = 0;
	if (syntax_parser(tmp))
	{
		singleton()->lrv = LRV_SYNTAX_ERROR;
		return ;
	}
	if (tmp)
		fork_fd(tmp);
	while (tmp)
	{
		cmd_up(tmp);
		exec_all_in_one(tmp);
		while (tmp && flag_check(tmp) != FLG_EO_CMD)
			tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
	}
	unlink_all_tmp_fd(i);
}
