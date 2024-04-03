/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiozsert <wiozsert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 11:28:07 by wiozsert          #+#    #+#             */
/*   Updated: 2020/08/27 02:15:22 by wiozsert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int			small_squart(int left_sq, int top_sq, int diago_sq)
{
	int small_sq;

	small_sq = 0;
	small_sq = (left_sq < top_sq) ? left_sq : top_sq;
	small_sq = (diago_sq < small_sq) ? diago_sq : small_sq;
	return (small_sq);
}

t_squart	check_sq(int **map)
{
	int			i;
	int			j;
	t_squart	sq;

	i = -1;
	sq.len = 0;
	while (map[++i] != NULL)
	{
		j = -1;
		while (map[i][++j] != '\n')
		{
			if (i == 0 || j == 0)
				map[i][j] = 1;
			if (map[i][j] == 1 && i > 0 && j > 0)
				map[i][j] = small_squart(map[i - 1][j], map[i][j - 1],
						map[i - 1][j - 1]) + 1;
			if (sq.len < map[i][j])
			{
				sq.len = map[i][j];
				sq.i = i;
				sq.j = j;
			}
		}
	}
	return (sq);
}
