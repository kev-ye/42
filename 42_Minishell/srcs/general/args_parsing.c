/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 12:16:35 by besellem          #+#    #+#             */
/*   Updated: 2021/06/22 16:53:38 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	option_c(int ac, const char **av)
{
	if (ac >= 3)
	{
		ft_parse((char *)av[2]);
		ft_exec_each_cmd(singleton()->lst);
	}
}

void	parse_args(int ac, const char **av)
{
	ft_bzero(&singleton()->option, sizeof(struct s_options));
	singleton()->option.fd = STDIN_FILENO;
	if (ac > 1)
	{
		if (0 == ft_strcmp((char *)av[1], "-c"))
		{
			singleton()->option.opt_c = TRUE;
			if (ac < 3)
			{
				ft_dprintf(2, PROG_NAME ": -c: option requires an argument\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			singleton()->isatty_stdin = 0;
			singleton()->option.fd = open(av[1], O_RDONLY);
			if (singleton()->option.fd == -1)
			{
				ft_dprintf(2, PROG_NAME ": %s: %s\n", av[1], strerror(errno));
				ft_free_exit(EXIT_FAILURE);
			}
		}
	}
}
