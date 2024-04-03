/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 11:53:08 by kaye              #+#    #+#             */
/*   Updated: 2021/02/08 12:35:31 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	turn_left(t_win *win)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = win->camera->dir_x;
	old_plane_x = win->camera->plane_x;
	win->camera->dir_x = win->camera->dir_x
		* cos(-win->camera->rot_speed)
		- win->camera->dir_y
		* sin(-win->camera->rot_speed);
	win->camera->dir_y = old_dir_x
		* sin(-win->camera->rot_speed)
		+ win->camera->dir_y
		* cos(-win->camera->rot_speed);
	win->camera->plane_x = win->camera->plane_x
		* cos(-win->camera->rot_speed)
		- win->camera->plane_y
		* sin(-win->camera->rot_speed);
	win->camera->plane_y = old_plane_x
		* sin(-win->camera->rot_speed)
		+ win->camera->plane_y
		* cos(-win->camera->rot_speed);
}

void	turn_right(t_win *win)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = win->camera->dir_x;
	old_plane_x = win->camera->plane_x;
	win->camera->dir_x = win->camera->dir_x
		* cos(win->camera->rot_speed)
		- win->camera->dir_y
		* sin(win->camera->rot_speed);
	win->camera->dir_y = old_dir_x
		* sin(win->camera->rot_speed)
		+ win->camera->dir_y
		* cos(win->camera->rot_speed);
	win->camera->plane_x = win->camera->plane_x
		* cos(win->camera->rot_speed)
		- win->camera->plane_y
		* sin(win->camera->rot_speed);
	win->camera->plane_y = old_plane_x
		* sin(win->camera->rot_speed)
		+ win->camera->plane_y
		* cos(win->camera->rot_speed);
}

void	turn_up(t_win *win)
{
	if (win->camera->cam_height < 2)
		win->camera->cam_height += win->camera->rot_speed;
}

void	turn_down(t_win *win)
{
	if (win->camera->cam_height > 0)
		win->camera->cam_height -= win->camera->rot_speed;
}
