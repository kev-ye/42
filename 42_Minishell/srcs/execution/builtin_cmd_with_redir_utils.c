/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd_with_redir_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 23:18:01 by kaye              #+#    #+#             */
/*   Updated: 2021/06/26 23:41:36 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*msg_error_with_exit(int opt, t_list *cmd)
{
	if (opt == 1)
	{
		ft_dprintf(STDERR_FILENO, PROG_NAME": %s: %s\n",
			((t_cmd *)cmd->content)->args[0], strerror(errno));
		return (NULL);
	}
	else if (opt == 2)
		return (NULL);
	return (NULL);
}

static t_list	*parser_input_fd(t_list *cmd, int *fd_input, int flag_is)
{
	char	*tmp_fd_name;
	int		i;

	tmp_fd_name = NULL;
	i = 0;
	if (flag_is == F_INPUT)
	{
		*fd_input = open(((t_cmd *)cmd->content)->args[0], O_RDWR);
		if (*fd_input == -1)
			cmd = msg_error_with_exit(1, cmd);
		else
			close(*fd_input);
	}
	else if (flag_is == F_DINPUT)
	{
		tmp_fd_name = get_tmp_fd(i);
		*fd_input = open(tmp_fd_name, O_RDWR);
		free(tmp_fd_name);
		if (*fd_input == -1)
			cmd = msg_error_with_exit(2, cmd);
		else
			close(*fd_input);
	}
	return (cmd);
}

int	builtin_redir_parser(t_list *cmd, int *fd_input, int *fd_output)
{
	int	first;
	int	flag_is;

	(void)fd_output;
	flag_is = 0;
	first = 1;
	while (cmd)
	{
		if (first == 1)
			first = 0;
		else if (!first && (flag_is == F_INPUT || flag_is == F_DINPUT))
		{
			cmd = parser_input_fd(cmd, fd_input, flag_is);
			if (!cmd)
				return (ERROR);
		}
		flag_is = check_for_next(cmd);
		if (!flag_is)
			return (SUCCESS);
		cmd = cmd->next;
	}
	return (SUCCESS);
}
