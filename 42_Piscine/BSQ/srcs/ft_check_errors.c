/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiozsert <wiozsert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 19:58:21 by wiozsert          #+#    #+#             */
/*   Updated: 2020/08/27 10:53:58 by wiozsert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_check_valid_tray(int *str, t_solver solver)
{
	int i;

	i = 0;
	while (str[i - 1] != '\n')
		i++;
	if (ft_check_if_tray_is_empy(str) == 0 ||
		ft_check_if_line_are_same_length(str, i, 0, 0) == 0 ||
		ft_check_if_char_is_found(str, solver.empty, solver.obstacle) == 0 ||
		ft_check_if_char_is_missing(str, solver.obstacle, solver.empty) == 0 ||
		ft_check_if_tray_is_full_of_obstacle(str) == 0)
	{
		ft_putstr_error("map error\n");
		free(str);
		return (0);
	}
	return (1);
}
