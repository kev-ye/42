/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:56:10 by kaye              #+#    #+#             */
/*   Updated: 2021/03/02 11:48:50 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void			free_split(char **s)
{
	int count;

	count = 0;
	while (s[count] != NULL)
		free(s[count++]);
	free(s[count]);
	free(s);
}

static void		free_path(t_desc_info *desc_info)
{
	if (desc_info->path_no)
		free(desc_info->path_no);
	if (desc_info->path_so)
		free(desc_info->path_so);
	if (desc_info->path_we)
		free(desc_info->path_we);
	if (desc_info->path_ea)
		free(desc_info->path_ea);
	if (desc_info->path_s)
		free(desc_info->path_s);
	if (desc_info->path_s)
		free(desc_info->path_m);
	if (desc_info->path_s)
		free(desc_info->path_b);
	if (desc_info->path_s)
		free(desc_info->path_l);
	if (desc_info->path_s)
		free(desc_info->path_g);
}

void			free_desc_info(t_desc_info *desc_info)
{
	int i;

	i = 0;
	free_path(desc_info);
	if (desc_info->map)
	{
		while (i < desc_info->map_y)
		{
			if (desc_info->map[i])
				free(desc_info->map[i]);
			i++;
		}
		free(desc_info->map);
	}
	free(desc_info);
}

static void		free_win2(t_win *win)
{
	if (win->save)
		if (win->mlx_ptr != NULL)
			free(win->mlx_ptr);
	if (win != NULL)
		free(win);
}

void			free_win(t_win *win)
{
	free_img_tex(win);
	free_img_sprite(win);
	free_img_effect(win);
	if (win->img != NULL)
	{
		mlx_destroy_image(win->mlx_ptr, win->img->img_ptr);
		free(win->img);
	}
	if (win->key_code != NULL)
		free(win->key_code);
	if (win->camera != NULL)
		free(win->camera);
	if (win->desc_info != NULL)
		free_desc_info(win->desc_info);
	free_win2(win);
}
