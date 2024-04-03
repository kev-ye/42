/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texInitialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:03:52 by kaye              #+#    #+#             */
/*   Updated: 2021/11/29 23:36:56 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	_set_tex(t_img *tex, int index)
{
	t_cub3d const	*ptr = sglt();

	tex->img_ptr = mlx_xpm_file_to_image(
			ptr->mlx_ptr,
			ptr->map_info.path[index],
			&tex->width,
			&tex->height
			);
	if (NULL == tex->img_ptr)
		exit_clean(E_IMG, __FILE__, __LINE__);
	tex->addr = mlx_get_data_addr(
			tex->img_ptr,
			&tex->bpp,
			&tex->size,
			&tex->endian
			);
}

void	tex_initialize(void)
{
	int	i;

	i = 0;
	while (i < TEXMAX)
	{
		_set_tex(&sglt()->tex_img[i], i);
		++i;
	}
}
