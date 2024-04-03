/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_desc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:57:11 by kaye              #+#    #+#             */
/*   Updated: 2021/02/09 10:14:05 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_desc_info		*init_desc_info(void)
{
	t_desc_info *new_info;

	if (!(new_info = malloc(sizeof(t_desc_info))))
		return (NULL);
	ft_bzero(&new_info->desc, sizeof(t_desc));
	new_info->r_x = -1;
	new_info->r_y = -1;
	new_info->path_no = NULL;
	new_info->path_so = NULL;
	new_info->path_we = NULL;
	new_info->path_ea = NULL;
	new_info->path_s = NULL;
	new_info->path_m = NULL;
	new_info->path_b = NULL;
	new_info->path_l = NULL;
	new_info->path_g = NULL;
	new_info->color_f = -1;
	new_info->color_c = -1;
	new_info->player_x = -99;
	new_info->player_y = -99;
	new_info->player_dir = -99;
	new_info->map = NULL;
	new_info->map_y = 0;
	new_info->map_x = 0;
	return (new_info);
}
