/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_line_id_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:11:45 by kaye              #+#    #+#             */
/*   Updated: 2021/02/23 14:41:18 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int		check_file_line_info_4(
		char *line,
		t_desc **desc,
		t_desc_info *desc_info)
{
	if (line[0] == 'L' && line[1] == ' ')
	{
		if (!(get_path(line, desc_info)))
			return (0);
		(*desc)->l++;
	}
	else if (line[0] == 'M' && line[1] == ' ')
	{
		if (!(get_path(line, desc_info)))
			return (0);
		(*desc)->m++;
	}
	else if (line[0] == 'G' && line[1] == ' ')
	{
		if (!(get_path(line, desc_info)))
			return (0);
		(*desc)->g++;
	}
	else
		return (0);
	return (1);
}

static int		check_file_line_info_3(
		char *line,
		t_desc **desc,
		t_desc_info *desc_info)
{
	if (line[0] == 'W' && !ft_strncmp(line, "WE", 2))
	{
		if (!(get_path(line, desc_info)))
			return (0);
		(*desc)->we++;
	}
	else if (line[0] == 'E' && !ft_strncmp(line, "EA", 2))
	{
		if (!(get_path(line, desc_info)))
			return (0);
		(*desc)->ea++;
	}
	else if (line[0] == 'B' && line[1] == ' ')
	{
		if (!(get_path(line, desc_info)))
			return (0);
		(*desc)->b++;
	}
	else if (!(check_file_line_info_4(line, desc, desc_info)))
		return (0);
	return (1);
}

static int		check_file_line_info_2(
		char *line,
		t_desc **desc,
		t_desc_info *desc_info)
{
	if (line[0] == 'C' && line[1] == ' ')
	{
		if (!(get_ceiling_color(line, desc_info)))
			return (0);
		(*desc)->c++;
	}
	else if (line[0] == 'N' && !ft_strncmp(line, "NO", 2))
	{
		if (!(get_path(line, desc_info)))
			return (0);
		(*desc)->no++;
	}
	else if (line[0] == 'S' && !ft_strncmp(line, "SO", 2))
	{
		if (!(get_path(line, desc_info)))
			return (0);
		(*desc)->so++;
	}
	else if (!(check_file_line_info_3(line, desc, desc_info)))
		return (0);
	return (1);
}

static int		check_file_line_info(
		char *line,
		t_desc *desc,
		t_desc_info *desc_info)
{
	if (line[0] == 'R' && line[1] == ' ')
	{
		if (!(get_resoltion(line, desc_info)))
			return (0);
		desc->r++;
	}
	else if (line[0] == 'S' && line[1] == ' ')
	{
		if (!(get_path(line, desc_info)))
			return (0);
		desc->s++;
	}
	else if (line[0] == 'F' && line[1] == ' ')
	{
		if (!(get_floor_color(line, desc_info)))
			return (0);
		desc->f++;
	}
	else if (!(check_file_line_info_2(line, &desc, desc_info)))
		return (0);
	return (1);
}

int				check_file_line(
		char *line,
		t_desc *desc,
		t_desc_info *desc_info)
{
	if (!*line)
		return (1);
	if (line[0] == 'R' || line[0] == 'S' || line[0] == 'F' ||
			line[0] == 'N' || line[0] == 'W' || line[0] == 'E' ||
			line[0] == 'C' || line[0] == 'B' || line[0] == 'L' ||
			line[0] == 'M' || line[0] == 'G')
	{
		if (check_file_line_info(line, desc, desc_info)
				&& check_file_line_info_done(*desc))
			return (1);
		else
			return (0);
	}
	else
		return (0);
	return (1);
}
