/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 11:49:21 by kaye              #+#    #+#             */
/*   Updated: 2021/02/16 11:15:03 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_texture(
		t_win *win,
		const char *path,
		int index)
{
	if (!(win->texture[index]->img_ptr = mlx_xpm_file_to_image(win->mlx_ptr,
					(char *)path, &win->texture[index]->width,
					&win->texture[index]->height)))
		return (0);
	win->texture[index]->addr = mlx_get_data_addr(win->texture[index]->img_ptr,
			&win->texture[index]->bpp, &win->texture[index]->line_len,
			&win->texture[index]->endian);
	return (1);
}

int		load_texture(t_win *win)
{
	int tex_1;
	int tex_2;
	int tex_3;
	int tex_4;

	tex_1 = set_texture(win, win->desc_info->path_no, 0);
	tex_2 = set_texture(win, win->desc_info->path_so, 1);
	tex_3 = set_texture(win, win->desc_info->path_ea, 2);
	tex_4 = set_texture(win, win->desc_info->path_we, 3);
	if (!tex_1 || !tex_2 || !tex_3 || !tex_4)
		return (0);
	return (1);
}

int		init_tex(t_win *win)
{
	if (!(win->texture = malloc(sizeof(t_img *) * 4)))
		return (0);
	if (!(win->texture[0] = malloc(sizeof(t_img))))
		return (0);
	if (!(win->texture[1] = malloc(sizeof(t_img))))
		return (0);
	if (!(win->texture[2] = malloc(sizeof(t_img))))
		return (0);
	if (!(win->texture[3] = malloc(sizeof(t_img))))
		return (0);
	ft_bzero(win->texture[0], sizeof(t_img));
	ft_bzero(win->texture[1], sizeof(t_img));
	ft_bzero(win->texture[2], sizeof(t_img));
	ft_bzero(win->texture[3], sizeof(t_img));
	if (!(load_texture(win)))
		return (0);
	return (1);
}
