/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:17:41 by kaye              #+#    #+#             */
/*   Updated: 2021/06/21 19:05:29 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_opt_n(char *opt)
{
	int	i;

	i = 0;
	if (opt && opt[i] && !ft_strncmp(opt, "-", 1) && opt[i + 1])
	{
		++i;
		while (opt[i])
		{
			if (opt[i] && ft_strncmp(opt + i, "n", 1) != 0)
				return (0);
			++i;
		}
	}
	else
		return (0);
	return (1);
}

static int	cmd_parse_opt_n(char **cmd)
{
	int	i;

	i = 1;
	while (cmd && cmd[i])
	{
		if (check_opt_n(cmd[i]))
			++i;
		else
			return (i);
	}
	return (i);
}

static void	echo_print_opt_n(t_cmd *cmds, int len_cmd, int i)
{
	while (i < len_cmd)
	{
		ft_dprintf(STDOUT_FILENO, "%s", cmds->args[i++]);
		if (i < len_cmd)
			ft_dprintf(STDOUT_FILENO, " ");
	}
}

static void	echo_print(t_cmd *cmds, int len_cmd, int i)
{
	while (i < len_cmd && cmds->args[i])
	{
		ft_dprintf(STDOUT_FILENO, "%s", cmds->args[i++]);
		if (i < len_cmd)
			ft_dprintf(STDOUT_FILENO, " ");
	}
	ft_dprintf(STDOUT_FILENO, "\n");
}

int	ft_echo(t_cmd *cmds)
{
	int	len_cmd;
	int	i;

	i = 0;
	if (!cmds || !cmds->args || !*cmds->args)
		return (ERROR);
	len_cmd = ft_strslen(cmds->args);
	i = cmd_parse_opt_n(cmds->args);
	if (*cmds->args && *(cmds->args + 1) && i >= 2)
		echo_print_opt_n(cmds, len_cmd, i);
	else
	{
		i = 1;
		echo_print(cmds, len_cmd, i);
	}
	return (SUCCESS);
}
