/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxClean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:52:54 by kaye              #+#    #+#             */
/*   Updated: 2021/11/25 17:38:11 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	_main_img_clean(t_cub3d	*ptr)
{
	if (NULL != ptr->mlx_img.img_ptr)
		mlx_destroy_image(ptr->mlx_ptr, ptr->mlx_img.img_ptr);
}

static void	_tex_img_clean(t_cub3d *ptr)
{
	int	i;

	i = 0;
	while (i < TEXMAX)
	{
		if (NULL != ptr->tex_img[i].img_ptr)
			mlx_destroy_image(ptr->mlx_ptr, ptr->tex_img[i].img_ptr);
		++i;
	}
}

void	mlx_clean(void)
{
	t_cub3d	*ptr;

	ptr = sglt();
	_main_img_clean(ptr);
	_tex_img_clean(ptr);
}
