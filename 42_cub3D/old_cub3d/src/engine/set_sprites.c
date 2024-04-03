/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 11:23:38 by kaye              #+#    #+#             */
/*   Updated: 2021/02/05 09:42:28 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			if (win->desc_info->map[y][x] == '2')
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
		const char *path)
{
	if (!(win->sprite->img_ptr = mlx_xpm_file_to_image(win->mlx_ptr,
					(char *)path, &win->sprite->width,
					&win->sprite->height)))
		return (0);
	win->sprite->addr = mlx_get_data_addr(win->sprite->img_ptr,
			&win->sprite->bpp, &win->sprite->line_len,
			&win->sprite->endian);
	return (1);
}

int			load_sprites(t_win *win)
{
	int sprite;

	if (!(sprite = set_sprites(win, win->desc_info->path_s)))
		return (0);
	return (1);
}

int			init_sprite(t_win *win)
{
	if (!(win->sprite = malloc(sizeof(t_img))))
		return (0);
	ft_bzero(win->sprite, sizeof(t_img));
	if (!(load_sprites(win)))
		return (0);
	return (1);
}
