/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_camera_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 09:52:20 by kaye              #+#    #+#             */
/*   Updated: 2021/02/18 09:41:19 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_camera		*set_player_dir_y(t_camera *camera_info, int dir)
{
	if (dir == 'N')
	{
		camera_info->dir_y = -1.0;
		camera_info->plane_y = 0.0;
	}
	else if (dir == 'S')
	{
		camera_info->dir_y = 1.0;
		camera_info->plane_y = 0.0;
	}
	else if (dir == 'W')
	{
		camera_info->dir_y = 0.0;
		camera_info->plane_y = -0.66;
	}
	else if (dir == 'E')
	{
		camera_info->dir_y = 0.0;
		camera_info->plane_y = 0.66;
	}
	return (camera_info);
}

static t_camera		*set_player_dir_x(t_camera *camera_info, int dir)
{
	if (dir == 'N')
	{
		camera_info->dir_x = 0.0;
		camera_info->plane_x = 0.66;
	}
	else if (dir == 'S')
	{
		camera_info->dir_x = 0.0;
		camera_info->plane_x = -0.66;
	}
	else if (dir == 'W')
	{
		camera_info->dir_x = -1.0;
		camera_info->plane_x = 0.0;
	}
	else if (dir == 'E')
	{
		camera_info->dir_x = 1.0;
		camera_info->plane_x = 0.0;
	}
	return (camera_info);
}

static t_camera		*set_player_dir(t_win *win, t_camera *camera_info)
{
	if (win->desc_info->player_dir == 'N')
	{
		camera_info = set_player_dir_x(camera_info, 'N');
		camera_info = set_player_dir_y(camera_info, 'N');
	}
	else if (win->desc_info->player_dir == 'S')
	{
		camera_info = set_player_dir_x(camera_info, 'S');
		camera_info = set_player_dir_y(camera_info, 'S');
	}
	else if (win->desc_info->player_dir == 'W')
	{
		camera_info = set_player_dir_x(camera_info, 'W');
		camera_info = set_player_dir_y(camera_info, 'W');
	}
	else if (win->desc_info->player_dir == 'E')
	{
		camera_info = set_player_dir_x(camera_info, 'E');
		camera_info = set_player_dir_y(camera_info, 'E');
	}
	return (camera_info);
}

int					init_camera(t_win *win)
{
	if (!(win->camera = malloc(sizeof(t_camera))))
		return (0);
	ft_bzero(win->camera, sizeof(t_camera));
	win->camera->pos_x = (double)win->desc_info->player_x + 0.5;
	win->camera->pos_y = (double)win->desc_info->player_y + 0.5;
	win->camera = set_player_dir(win, win->camera);
	win->camera->rot_speed = 0.10;
	win->camera->speed = 0.10;
	win->camera->cam_height = 1.0;
	win->player_life = 1.0;
	return (1);
}
