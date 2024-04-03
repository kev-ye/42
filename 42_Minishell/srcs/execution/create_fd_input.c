/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_fd_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 18:13:57 by kaye              #+#    #+#             */
/*   Updated: 2021/06/24 16:08:42 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_dinput_fd = O_RDWR | O_CREAT | O_TRUNC | O_APPEND;

static void	msg_error_with_exit(int opt)
{
	if (opt == 1)
		exit(LRV_GENERAL_ERROR);
	if (opt == 2)
	{
		ft_dprintf(STDERR_FILENO, PROG_NAME
			": maximum here-document count exceeded\n");
		ft_free_exit(2);
	}
}

static void	wait_dinput(t_list **cmd,
	char **input_str,
	char **tmp_fd,
	int *fd_input)
{
	while (1)
	{
		singleton()->rl_lvl = 2;
		*input_str = readline("> ");
		if (*input_str
			&& !ft_strcmp(*input_str, ((t_cmd *)(*cmd)->content)->args[0]))
		{
			free(*input_str);
			if (((t_cmd *)(*cmd)->content)->status_flag & FLG_DINPUT)
			{
				close(*fd_input);
				*fd_input = open(*tmp_fd, g_dinput_fd, 0666);
				if (*fd_input == -1)
					msg_error_with_exit(1);
				(*cmd) = (*cmd)->next;
				continue ;
			}
			else
				break ;
		}
		else if (!*input_str)
			break ;
		if (*input_str)
			ft_putendl_fd(*input_str, *fd_input);
	}
}

static int	check_max_dinput(t_list *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		++count;
		if (flag_check(cmd) != FLG_DINPUT)
			break ;
		cmd = cmd->next;
	}
	return (count);
}

static t_list	*create_input_fd(t_list *cmd, int fd_input, int flag_is)
{
	char	*input_str;
	char	*tmp_fd;
	int		i;

	i = 0;
	tmp_fd = NULL;
	input_str = NULL;
	if (flag_is == F_DINPUT)
	{
		if (check_max_dinput(cmd) > 16)
			msg_error_with_exit(2);
		tmp_fd = new_tmp_fd_name(i);
		fd_input = open(tmp_fd, g_dinput_fd, 0666);
		if (fd_input == -1)
			msg_error_with_exit(1);
		else
		{
			wait_dinput(&cmd, &input_str, &tmp_fd, &fd_input);
			if (fd_input != -1)
				close(fd_input);
			free(tmp_fd);
		}
	}
	return (cmd);
}

void	create_fd_input(t_list *cmd)
{
	int	first;
	int	fd_output;
	int	fd_input;
	int	flag_is;

	fd_output = -1;
	fd_input = -1;
	flag_is = 0;
	first = 1;
	while (cmd)
	{
		if (first == 1)
			first = 0;
		else if (!first && flag_is == F_DINPUT)
			cmd = create_input_fd(cmd, fd_input, flag_is);
		flag_is = check_for_next(cmd);
		cmd = cmd->next;
	}
}
