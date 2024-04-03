/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_char_to_solve_for_one.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiozsert <wiozsert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 00:28:33 by wiozsert          #+#    #+#             */
/*   Updated: 2020/08/27 08:39:45 by wiozsert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_get_obstacle_for_one(char *str, int *obstacle)
{
	int		i;

	i = 0;
	while (str[i] != '\n')
		i++;
	*obstacle = str[i - 2];
}

void	ft_get_empty_for_one(char *str, int *empty)
{
	int		i;

	i = 0;
	while (str[i] != '\n')
		i++;
	*empty = str[i - 3];
}

void	ft_get_fill_for_one(char *str, int *fill)
{
	int		i;

	i = 0;
	while (str[i] != '\n')
		i++;
	*fill = str[i - 1];
}
