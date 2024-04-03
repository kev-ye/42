/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:49:37 by kaye              #+#    #+#             */
/*   Updated: 2021/02/05 09:57:27 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		check_map_x2(char **map, int y, int x, int get_wall)
{
	while (x >= 0)
	{
		if (map[y][x] == ' ')
			return (0);
		if (map[y][x] == '1')
		{
			get_wall++;
			break ;
		}
		if (map[y][x] != '0' && map[y][x] != '2')
			return (0);
		--x;
	}
	return (get_wall);
}

int				check_map_x(char **map, int y, int x)
{
	int tmp_x;
	int get_wall;

	tmp_x = x;
	get_wall = 0;
	while (map[y][x])
	{
		if (map[y][x] == ' ')
			return (0);
		if (map[y][x] == '1')
		{
			get_wall++;
			break ;
		}
		if (map[y][x] != '0' && map[y][x] != '2')
			return (0);
		++x;
	}
	x = tmp_x;
	get_wall = check_map_x2(map, y, x, get_wall);
	if (get_wall == 2)
		return (1);
	return (0);
}
