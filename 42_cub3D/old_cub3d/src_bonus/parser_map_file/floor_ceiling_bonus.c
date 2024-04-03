/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:02:39 by kaye              #+#    #+#             */
/*   Updated: 2021/03/01 16:08:29 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int		color_is_true(int color, char *s)
{
	if (color == -1)
	{
		free(s);
		return (0);
	}
	return (1);
}

int				get_floor_color(char *line, t_desc_info *desc_info)
{
	char *s;

	if (ft_strncmp(line, "F", 1) != 0)
		return (0);
	if (!(s = ft_substr(line, 1, ft_strlen(line) - 1)))
		return (0);
	desc_info->color_f = check_and_get_color(s);
	if (!(color_is_true(desc_info->color_f, s)))
		return (0);
	free(s);
	return (1);
}

int				get_ceiling_color(char *line, t_desc_info *desc_info)
{
	char *s;

	if (ft_strncmp(line, "C", 1) != 0)
		return (0);
	if (!(s = ft_substr(line, 1, ft_strlen(line) - 1)))
		return (0);
	desc_info->color_c = check_and_get_color(s);
	if (!(color_is_true(desc_info->color_c, s)))
		return (0);
	free(s);
	return (1);
}
