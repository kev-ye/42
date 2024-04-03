/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_img_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:23:00 by kaye              #+#    #+#             */
/*   Updated: 2021/02/16 11:38:54 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void		free_img_tex(t_win *win)
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

void		free_img_sprite(t_win *win)
{
	if (win->sprite != NULL)
	{
		if (win->sprite[0] != NULL)
		{
			mlx_destroy_image(win->mlx_ptr, win->sprite[0]->img_ptr);
			free(win->sprite[0]);
		}
		if (win->sprite[1] != NULL)
		{
			mlx_destroy_image(win->mlx_ptr, win->sprite[1]->img_ptr);
			free(win->sprite[1]);
		}
		if (win->sprite[2] != NULL)
		{
			mlx_destroy_image(win->mlx_ptr, win->sprite[2]->img_ptr);
			free(win->sprite[2]);
		}
		free(win->sprite);
	}
}

void		free_img_effect(t_win *win)
{
	if (win->gun != NULL)
	{
		mlx_destroy_image(win->mlx_ptr, win->gun->img_ptr);
		free(win->gun);
	}
	if (win->life != NULL)
	{
		mlx_destroy_image(win->mlx_ptr, win->life->img_ptr);
		free(win->life);
	}
	if (win->mini_map != NULL)
	{
		mlx_destroy_image(win->mlx_ptr, win->mini_map->img_ptr);
		free(win->mini_map);
	}
}
