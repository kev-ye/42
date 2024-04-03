/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 14:46:59 by kaye              #+#    #+#             */
/*   Updated: 2021/07/05 19:58:11 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define TEX_WALL "./tex/wall.xpm"
#define TEX_EMPTY "./tex/floor.xpm"
#define TEX_COLLECT "./tex/key.xpm"
#define TEX_EXIT "./tex/closed_door.xpm"
#define TEX_PLAYER "./tex/knight.xpm"

const char	*g_tex_path[] = {TEX_WALL,
	TEX_EMPTY,
	TEX_COLLECT,
	TEX_EXIT,
	TEX_PLAYER};

static void	set_tex(int tex_i, char *path)
{
	const int	fd = open(path, O_RDONLY);

	if (fd == -1)
		__exit__(E_MALLOC, NULL, NOTHING, FAILURE);
	singleton()->tex[tex_i].img_ptr = mlx_xpm_file_to_image(
		singleton()->mlx_ptr,
		path,
		&singleton()->tex[tex_i].width,
		&singleton()->tex[tex_i].height);
	if (!singleton()->tex[tex_i].img_ptr)
		__exit__(E_MALLOC, NULL, NOTHING, FAILURE);
	singleton()->tex[tex_i].addr = mlx_get_data_addr(
		singleton()->tex[tex_i].img_ptr,
		&singleton()->tex[tex_i].bpp,
		&singleton()->tex[tex_i].line_len,
		&singleton()->tex[tex_i].endian);
}

void	load_tex(void)
{
	int	i;

	i = 0;
	while (i < TEX_NBR)
	{
		set_tex(i, (char *)g_tex_path[i]);
		++i;
	}
}
