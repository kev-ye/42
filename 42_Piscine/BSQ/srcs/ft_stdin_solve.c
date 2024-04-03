/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdin_solve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiozsert <wiozsert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 02:56:11 by wiozsert          #+#    #+#             */
/*   Updated: 2020/08/27 11:23:20 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		*ft_copy_stin_in_tab(int *buffer)
{
	int		rd;
	int		i;
	char	c;

	rd = 1;
	i = 0;
	while (rd > 0)
	{
		rd = read(STDIN_FILENO, &c, 1);
		buffer[i] = c;
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

int		ft_resolve_tray_one_ac(int *buffer)
{
	t_solver	solver;
	t_squart	sq;
	int			**tab;
	int			**stock;

	(void)sq;
	(void)solver;
	stock = NULL;
	tab = NULL;
	buffer = ft_copy_stin_in_tab(buffer);
	ft_get_empty(buffer, &solver.empty);
	ft_get_obstacle(buffer, &solver.obstacle);
	if (ft_check_valid_tray(buffer, solver))
	{
		ft_get_fill(buffer, &solver.fill);
		tab = ft_init_tab_from_str(buffer, tab);
		stock = ft_init_stock(stock, tab, solver.empty, solver.obstacle);
		sq = check_sq(stock);
		tab = replace_tab(tab, sq, solver.fill);
		show_tab(tab);
		ft_free_for_all(tab, stock, solver);
	}
	return (1);
}
