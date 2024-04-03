/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_line_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:16:25 by kaye              #+#    #+#             */
/*   Updated: 2021/02/24 16:18:42 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_map_ready(t_desc desc)
{
	if (desc.r == 1 && desc.no == 1 && desc.so == 1 && desc.we == 1 &&
			desc.ea == 1 && desc.s == 1 && desc.f == 1 && desc.c == 1)
	{
		return (1);
	}
	return (0);
}

int		check_no_map(char *line, t_desc *desc)
{
	int i;

	i = 0;
	if (!line[0])
	{
		desc->map = 0;
		return (1);
	}
	while (line[i])
	{
		if (ft_isspace(line[i]) || line[i] == '0' || line[i] == '1'
				|| line[i] == '2' || line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'E' || line[i] == 'W')
		{
			desc->map = 1;
			i++;
		}
		else
			return (0);
	}
	return (1);
}

int		check_map_norm(char *line)
{
	int i;

	i = 0;
	if (!line[0])
		return (0);
	while (line[i])
	{
		if (ft_isspace(line[i]) || line[i] == '0' || line[i] == '1'
				|| line[i] == '2' || line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'E' || line[i] == 'W')
			i++;
		else
			return (0);
	}
	return (1);
}
