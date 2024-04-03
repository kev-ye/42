/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_resolution_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:00:07 by kaye              #+#    #+#             */
/*   Updated: 2021/02/16 14:09:13 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	check_resolution_id(char **s, int count)
{
	if (count != 3)
	{
		free_split(s);
		return (0);
	}
	if (ft_strcmp(s[0], "R"))
	{
		free_split(s);
		return (0);
	}
	return (1);
}

static int	check_resolution(char **s, int i)
{
	int count;

	count = 0;
	while (s[i][count])
		if (!ft_isdigit(s[i][count++]))
		{
			free_split(s);
			return (0);
		}
	return (1);
}

int			get_resoltion(char *line, t_desc_info *desc_info)
{
	int		count;
	char	**s;

	count = 0;
	if (!(s = ft_split(line, ' ')))
		return (0);
	while (s[count] != NULL)
		++count;
	if (!(check_resolution_id(s, count)))
		return (0);
	if (!(check_resolution(s, 1)))
		return (0);
	if (!(check_resolution(s, 2)))
		return (0);
	desc_info->r_x = ft_atoi(s[1]);
	desc_info->r_y = ft_atoi(s[2]);
	free_split(s);
	if (desc_info->r_x < 1 || desc_info->r_y < 1)
		return (0);
	return (1);
}
