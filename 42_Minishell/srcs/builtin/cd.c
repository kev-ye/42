/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:11:08 by kaye              #+#    #+#             */
/*   Updated: 2021/06/23 16:12:23 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_home(void)
{
	if (chdir(getenv("HOME")) == -1)
	{
		ft_dprintf(STDERR_FILENO, PROG_NAME": cd: HOME not set\n");
		return (ERROR);
	}
	return (SUCCESS);
}

int	ft_cd(t_cmd *cmds)
{
	char	*old_pwd;

	if (!cmds || !cmds->args || !*cmds->args)
		return (ERROR);
	if (ft_strslen(cmds->args) > 2)
	{
		ft_dprintf(STDERR_FILENO, PROG_NAME": cd: too many arguments\n");
		return (ERROR);
	}
	if (*cmds->args && !*(cmds->args + 1))
		if (cd_home() == ERROR)
			return (ERROR);
	if (*cmds->args && *(cmds->args + 1) && chdir(cmds->args[1]) == -1)
	{
		ft_dprintf(STDERR_FILENO, PROG_NAME": cd: %s: %s\n",
			cmds->args[1], strerror(errno));
		return (ERROR);
	}
	else
	{
		old_pwd = get_old_pwd();
		update_pwd_env(old_pwd);
		ft_memdel((void **)&old_pwd);
	}
	return (SUCCESS);
}
