/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapParsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:57:41 by kaye              #+#    #+#             */
/*   Updated: 2021/11/23 19:58:23 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_parsing(void)
{
	int	i;
	int	j;

	i = 0;
	while (NULL != sglt()->map_info.map && NULL != sglt()->map_info.map[i])
	{
		printf(S_PURPLE"MAP:%5c"S_NONE"%s\n", ' ', sglt()->map_info.map[i]);
		j = 0;
		while ('\0' != sglt()->map_info.map[i][j])
		{
			horizontal_check(sglt()->map_info.map[i], j);
			vertical_check(sglt()->map_info.map, i, j);
			++j;
		}
		++i;
	}
}
