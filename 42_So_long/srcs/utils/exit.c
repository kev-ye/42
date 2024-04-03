/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:11:30 by kaye              #+#    #+#             */
/*   Updated: 2021/07/06 15:19:20 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* mlx_destroy_display() does not exist on macOS */
#if defined(__APPLE__) && defined(__MACH__)

static void	__singleton_clean__(void)
{
	int	i;

	if (singleton()->mlx_ptr)
	{
		if (singleton()->img)
		{
			mlx_destroy_image(singleton()->mlx_ptr, singleton()->img->img_ptr);
			__free__(singleton()->img);
		}
		i = 0;
		while (i < TEX_NBR)
			mlx_destroy_image(singleton()->mlx_ptr,
				singleton()->tex[i++].img_ptr);
		mlx_destroy_window(singleton()->mlx_ptr, singleton()->win_ptr);
		free(singleton()->mlx_ptr);
	}
	i = 0;
	if (singleton()->map)
	{
		while (singleton()->map[i])
			__free__(singleton()->map[i++]);
		__free__(singleton()->map[i]);
		__free__(singleton()->map);
	}
}

#else 

static void	__singleton_clean__(void)
{
	int	i;

	if (singleton()->mlx_ptr)
	{
		if (singleton()->img)
		{
			mlx_destroy_image(singleton()->mlx_ptr, singleton()->img->img_ptr);
			__free__(singleton()->img);
		}
		i = 0;
		while (i < TEX_NBR)
			mlx_destroy_image(singleton()->mlx_ptr,
				singleton()->tex[i++].img_ptr);
		mlx_destroy_window(singleton()->mlx_ptr, singleton()->win_ptr);
		mlx_destroy_display(singleton()->mlx_ptr);
		free(singleton()->mlx_ptr);
	}
	i = 0;
	if (singleton()->map)
	{
		while (singleton()->map[i])
			__free__(singleton()->map[i++]);
		__free__(singleton()->map[i]);
		__free__(singleton()->map);
	}
}

#endif

int	__exit__(char *msg, void *ptr, int fd, int ret)
{
	if (msg)
	{
		if (ret == FAILURE)
			ft_putstr("Error\n");
		ft_printf("%s\n", msg);
	}
	if (ptr)
		__free__(ptr);
	if (fd != NOTHING)
		close(fd);
	if (singleton())
	{
		__singleton_clean__();
		__free__((void *)singleton());
	}
	exit(ret);
}
