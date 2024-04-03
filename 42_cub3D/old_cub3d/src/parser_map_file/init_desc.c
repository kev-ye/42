/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_desc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:57:11 by kaye              #+#    #+#             */
/*   Updated: 2021/02/05 12:54:53 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_desc_info		*init_desc_info(void)
{
	t_desc_info		*new_info;
	t_desc			desc;

	if (!(new_info = malloc(sizeof(t_desc_info))))
		return (void *)0;
	new_info->r_x = -1;
	new_info->r_y = -1;
	new_info->path_no = NULL;
	new_info->path_so = NULL;
	new_info->path_we = NULL;
	new_info->path_ea = NULL;
	new_info->path_s = NULL;
	new_info->color_f = -1;
	new_info->color_c = -1;
	new_info->player_x = -99;
	new_info->player_y = -99;
	new_info->player_dir = -99;
	new_info->map = NULL;
	new_info->map_y = 0;
	new_info->map_x = 0;
	ft_bzero(&desc, sizeof(desc));
	new_info->desc = desc;
	return (new_info);
}
