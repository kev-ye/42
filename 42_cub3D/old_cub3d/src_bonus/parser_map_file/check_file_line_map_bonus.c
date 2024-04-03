/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_line_map_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:16:25 by kaye              #+#    #+#             */
/*   Updated: 2021/02/08 14:22:19 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		check_map_ready(t_desc desc)
{
	if (desc.r == 1 && desc.no == 1 && desc.so == 1 && desc.we == 1 &&
			desc.ea == 1 && desc.s == 1 && desc.f == 1 && desc.c == 1 &&
			desc.b == 1 && desc.l == 1 && desc.m == 1 && desc.g == 1)
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
		if (line[i] == ' ' || line[i] == '0' || line[i] == '1' || line[i] == '2'
				|| line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
				|| line[i] == 'W' || line[i] == '4' || line[i] == '3')
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
		if (line[i] == ' ' || line[i] == '0' || line[i] == '1' ||
				line[i] == '2' || line[i] == 'N' || line[i] == 'S' ||
				line[i] == 'E' || line[i] == 'W' || line[i] == '4' ||
				line[i] == '3')
			i++;
		else
			return (0);
	}
	return (1);
}
