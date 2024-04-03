/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 11:48:55 by kaye              #+#    #+#             */
/*   Updated: 2020/08/23 20:25:56 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush_02.h"

int		main(int ac, char **av)
{
	if (ac == 2)
	{
		if (check_argv_number(av[1]) && ft_strlen(av[1]) != 0)
			print_dic(av[1]);
		else
			ft_error(1);
	}
	else if (ac == 3)
	{
		if (ft_open_valid(av[1]) && check_dic(ft_open_malloc(av[1])))
		{
			if (check_argv_number(av[2]) && ft_strlen(av[2]) != 0)
				print_dic(av[2]);
			else
				ft_error(1);
		}
		else
			ft_error(2);
	}
	return (0);
}
