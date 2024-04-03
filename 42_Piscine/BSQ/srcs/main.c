/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiozsert <wiozsert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 09:41:08 by wiozsert          #+#    #+#             */
/*   Updated: 2020/08/27 11:59:31 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		main(int ac, char **av)
{
	int		map;
	int		buffer[30000];
	int		**tab;

	tab = NULL;
	map = 1;
	if (ac == 1)
	{
		ft_resolve_tray_one_ac(buffer);
		return (0);
	}
	else if (ac > 1)
	{
		while (map < ac)
		{
			ft_resolve_tray(av[map], tab);
			map++;
			if (map < ac)
				ft_putchar('\n');
		}
	}
	return (0);
}
