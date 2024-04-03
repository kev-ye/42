/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:06:33 by besellem          #+#    #+#             */
/*   Updated: 2021/06/22 13:11:35 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, const char **av, char **env)
{
	if (!ft_init_minishell(env))
		return (EXIT_FAILURE);
	if (singleton()->isatty_stdin)
		init_history();
	parse_args(ac, av);
	if (singleton()->option.opt_c)
		option_c(ac, av);
	else
		prompt();
	return (EXIT_SUCCESS);
}
