/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:56:10 by kaye              #+#    #+#             */
/*   Updated: 2021/03/02 11:48:34 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			free_split(char **s)
{
	int count;

	count = 0;
	while (s[count] != NULL)
		free(s[count++]);
	free(s[count]);
	free(s);
}

void			free_desc_info(t_desc_info *desc_info)
{
	int i;

	i = 0;
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

static void		destroy_img(t_win *win)
{
	if (win->texture != NULL)
	{
		if (win->texture[0] != NULL)
		{
			mlx_destroy_image(win->mlx_ptr, win->texture[0]->img_ptr);
			free(win->texture[0]);
		}
		if (win->texture[1] != NULL)
		{
			mlx_destroy_image(win->mlx_ptr, win->texture[1]->img_ptr);
			free(win->texture[1]);
		}
		if (win->texture[2] != NULL)
		{
			mlx_destroy_image(win->mlx_ptr, win->texture[2]->img_ptr);
			free(win->texture[2]);
		}
		if (win->texture[3] != NULL)
		{
			mlx_destroy_image(win->mlx_ptr, win->texture[3]->img_ptr);
			free(win->texture[3]);
		}
		free(win->texture);
	}
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
	destroy_img(win);
	if (win->sprite != NULL)
	{
		mlx_destroy_image(win->mlx_ptr, win->sprite->img_ptr);
		free(win->sprite);
	}
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
