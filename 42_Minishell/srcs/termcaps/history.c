/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 20:53:49 by besellem          #+#    #+#             */
/*   Updated: 2021/06/22 13:29:24 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define __DEFAULT_RIGHTS__ 0644

// home = ft_getenv("HOME"); -> line 23
static void	create_history(void)
{
	char	*path;
	char	*home;

	home = NULL;
	if (!home || !ft_is_openable(home, O_RDONLY))
	{
		if (home)
			free(home);
		home = getcwd(NULL, 0);
	}
	ft_asprintf(&path, "%s/" HISTORY_FILENAME, home);
	if (home)
		ft_memdel((void **)&home);
	if (!path)
		ft_error(ERR_MALLOC, __FILE__, __LINE__);
	singleton()->hist.path = path;
	singleton()->hist.fd = open(singleton()->hist.path,
		O_RDWR | O_CREAT | O_APPEND, __DEFAULT_RIGHTS__);
	if ((-1) == singleton()->hist.fd)
		ft_error(ERR_OPEN, __FILE__, __LINE__);
}

static void	add_existing_history(void)
{
	int		check;
	char	*ret;

	while (TRUE)
	{
		check = get_next_line(singleton()->hist.fd, &ret);
		if ((0 == ft_strlen(ret) || ft_strisall(ret, ft_isspace)))
		{
			ft_memdel((void **)&ret);
			if (check > 0)
				continue ;
			else
				break ;
		}
		if (check < 0)
			ft_error(ERR_MALLOC, __FILE__, __LINE__);
		add_history(ret);
		ft_memdel((void **)&ret);
		if (0 == check)
			break ;
	}
}

void	init_history(void)
{
	create_history();
	add_existing_history();
}

void	add2history(char *cmd)
{
	if (!cmd || ft_strisall(cmd, ft_isspace) || 0 == ft_strlen(cmd))
		return ;
	if (!ft_is_openable(singleton()->hist.path, O_RDONLY))
	{
		singleton()->hist.fd = open(singleton()->hist.path,
			O_RDWR | O_CREAT | O_APPEND, __DEFAULT_RIGHTS__);
		if (singleton()->hist.fd == -1)
			ft_error(ERR_OPEN, __FILE__, __LINE__);
	}
	ft_putendl_fd(cmd, singleton()->hist.fd);
	add_history(cmd);
}
