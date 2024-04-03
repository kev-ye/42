/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprites_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 11:23:38 by kaye              #+#    #+#             */
/*   Updated: 2021/02/08 15:34:35 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int			get_sprite_amount(t_win *win)
{
	int count;
	int x;
	int y;

	count = 0;
	y = -1;
	while (++y < win->desc_info->map_y)
	{
		x = -1;
		while (++x < win->desc_info->map_x)
		{
			if (win->desc_info->map[y][x] == '2' ||
					win->desc_info->map[y][x] == '3' ||
					win->desc_info->map[y][x] == '4')
				++count;
		}
	}
	return (count);
}

t_sp_cast	*sprite_cast_init(t_win *win)
{
	t_sp_cast	*sp_cast;
	t_sprite	*sprite;
	int			count;

	count = get_sprite_amount(win);
	if (!(sprite = malloc(sizeof(t_sprite) * count)))
		return (NULL);
	ft_bzero(sprite, sizeof(t_sprite) * count);
	if (!(sp_cast = malloc(sizeof(t_sp_cast))))
		return (NULL);
	ft_bzero(sp_cast, sizeof(t_sp_cast));
	sp_cast->sp_amount = count;
	sp_cast->sprite = sprite;
	return (sp_cast);
}

int			set_sprites(
		t_win *win,
		const char *path,
		int index)
{
	if (!(win->sprite[index]->img_ptr = mlx_xpm_file_to_image(win->mlx_ptr,
					(char *)path, &win->sprite[index]->width,
					&win->sprite[index]->height)))
		return (0);
	win->sprite[index]->addr = mlx_get_data_addr(win->sprite[index]->img_ptr,
			&win->sprite[index]->bpp, &win->sprite[index]->line_len,
			&win->sprite[index]->endian);
	return (1);
}

int			load_sprites(t_win *win)
{
	if (!(set_sprites(win, win->desc_info->path_s, 0)))
		return (0);
	if (!(set_sprites(win, win->desc_info->path_b, 1)))
		return (0);
	if (!(set_sprites(win, win->desc_info->path_m, 2)))
		return (0);
	return (1);
}

int			init_sprite(t_win *win)
{
	if (!(win->sprite = malloc(sizeof(t_img *) * 3)))
		return (0);
	if (!(win->sprite[0] = malloc(sizeof(t_img))))
		return (0);
	if (!(win->sprite[1] = malloc(sizeof(t_img))))
		return (0);
	if (!(win->sprite[2] = malloc(sizeof(t_img))))
		return (0);
	ft_bzero(win->sprite[0], sizeof(t_img));
	ft_bzero(win->sprite[1], sizeof(t_img));
	ft_bzero(win->sprite[2], sizeof(t_img));
	if (!(load_sprites(win)))
		return (0);
	return (1);
}
