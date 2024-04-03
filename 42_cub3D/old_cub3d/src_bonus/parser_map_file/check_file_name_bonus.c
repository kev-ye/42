/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_name_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:06:12 by kaye              #+#    #+#             */
/*   Updated: 2021/02/08 14:22:59 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		check_file_name(const char *path)
{
	const char *tmp_path;

	if (!path)
		return (0);
	tmp_path = path;
	if ((path = ft_strrchr(path, '.')) && !ft_strcmp(path, ".cub"))
	{
		path = tmp_path;
		return (1);
	}
	return (0);
}
