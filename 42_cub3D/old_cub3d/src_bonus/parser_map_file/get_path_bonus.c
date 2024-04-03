/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:04:26 by kaye              #+#    #+#             */
/*   Updated: 2021/02/08 14:44:19 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int		get_path_4(char **s, t_desc_info ***desc_info)
{
	if (!ft_strcmp(s[0], "M"))
	{
		(**desc_info)->path_m = ft_strdup(s[1]);
		return (1);
	}
	else if (!ft_strcmp(s[0], "G"))
	{
		(**desc_info)->path_g = ft_strdup(s[1]);
		return (1);
	}
	return (0);
}

static int		get_path_3(char **s, t_desc_info ***desc_info)
{
	if (!ft_strcmp(s[0], "S"))
	{
		(**desc_info)->path_s = ft_strdup(s[1]);
		return (1);
	}
	else if (!ft_strcmp(s[0], "B"))
	{
		(**desc_info)->path_b = ft_strdup(s[1]);
		return (1);
	}
	else if (!ft_strcmp(s[0], "L"))
	{
		(**desc_info)->path_l = ft_strdup(s[1]);
		return (1);
	}
	else if (get_path_4(s, desc_info))
		return (1);
	return (0);
}

static int		get_path_2(char **s, t_desc_info **desc_info)
{
	if (!ft_strncmp(s[0], "NO", 2))
	{
		(*desc_info)->path_no = ft_strdup(s[1]);
		return (1);
	}
	else if (!ft_strncmp(s[0], "SO", 2))
	{
		(*desc_info)->path_so = ft_strdup(s[1]);
		return (1);
	}
	else if (!ft_strncmp(s[0], "WE", 2))
	{
		(*desc_info)->path_we = ft_strdup(s[1]);
		return (1);
	}
	else if (!ft_strncmp(s[0], "EA", 2))
	{
		(*desc_info)->path_ea = ft_strdup(s[1]);
		return (1);
	}
	else if (get_path_3(s, &desc_info))
		return (1);
	return (0);
}

int				get_path(char *line, t_desc_info *desc_info)
{
	int		count;
	char	**s;

	count = 0;
	if (!(s = ft_split(line, ' ')))
		return (0);
	while (s[count] != NULL)
		++count;
	if (count != 2)
	{
		free_split(s);
		return (0);
	}
	if (!get_path_2(s, &desc_info))
	{
		free_split(s);
		return (0);
	}
	free_split(s);
	return (1);
}
