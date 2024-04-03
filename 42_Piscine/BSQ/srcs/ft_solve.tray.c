/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve.tray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiozsert <wiozsert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 02:19:43 by wiozsert          #+#    #+#             */
/*   Updated: 2020/08/27 11:59:59 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_resolve_tray(char *tray, int **tab)
{
	int			**stock;
	t_solver	solver;
	t_squart	sq;

	stock = NULL;
	tab = NULL;
	solver.string_tray = ft_init_str_from_file(tray, solver.string_tray);
	if (solver.string_tray == 0)
	{
		ft_putstr_error("map error\n");
		return (0);
	}
	ft_get_empty(solver.string_tray, &solver.empty);
	ft_get_obstacle(solver.string_tray, &solver.obstacle);
	if (ft_check_valid_tray(solver.string_tray, solver) == 1)
	{
		ft_get_fill(solver.string_tray, &solver.fill);
		tab = ft_init_tab_from_str(solver.string_tray, tab);
		stock = ft_init_stock(stock, tab, solver.empty, solver.obstacle);
		sq = check_sq(stock);
		tab = replace_tab(tab, sq, solver.fill);
		show_tab(tab);
		ft_free_for_all(tab, stock, solver);
	}
	return (0);
}
