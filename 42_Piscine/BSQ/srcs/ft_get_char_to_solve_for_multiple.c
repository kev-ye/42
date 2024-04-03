/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_char_to_solve_for_multiple.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiozsert <wiozsert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 00:28:33 by wiozsert          #+#    #+#             */
/*   Updated: 2020/08/27 11:22:53 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_get_obstacle(int *str, int *obstacle)
{
	int		i;

	i = 0;
	while (str[i] != '\n')
		i++;
	*obstacle = str[i - 2];
}

void	ft_get_empty(int *str, int *empty)
{
	int		i;

	i = 0;
	while (str[i] != '\n')
		i++;
	*empty = str[i - 3];
}

void	ft_get_fill(int *str, int *fill)
{
	int		i;

	i = 0;
	while (str[i] != '\n')
		i++;
	*fill = str[i - 1];
}
