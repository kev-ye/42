/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_show_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiozsert <wiozsert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 20:25:08 by kaye              #+#    #+#             */
/*   Updated: 2020/08/27 12:04:03 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		**replace_tab(int **map, t_squart sq, char fill)
{
	int i;
	int j;
	int len;
	int temp;

	i = 0;
	len = sq.len;
	temp = sq.j;
	while (i < len)
	{
		j = 0;
		sq.j = temp;
		while (j < len)
		{
			map[sq.i][sq.j] = fill;
			sq.j--;
			j++;
		}
		sq.i--;
		i++;
	}
	return (map);
}

void	show_tab(int **map)
{
	int i;
	int j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			ft_putchar(map[i][j]);
			j++;
		}
		i++;
	}
}
