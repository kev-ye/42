/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 17:34:15 by kaye              #+#    #+#             */
/*   Updated: 2021/07/05 20:00:10 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_ac(int ac)
{
	if (ac < 2)
		__exit__("Too few arguments", NULL, NOTHING, FAILURE);
	if (ac > 2)
		__exit__("Too much arguments", NULL, NOTHING, FAILURE);
}

static void	new_image(void)
{
	singleton()->img = ft_calloc(sizeof(t_img), 1);
	if (!singleton()->img)
		__exit__(E_MALLOC, NULL, NOTHING, FAILURE);
	singleton()->img->img_ptr = mlx_new_image(singleton()->mlx_ptr,
		WIDTH,
		HEIGTH);
	if (!singleton()->img->img_ptr)
		__exit__(E_MALLOC, NULL, NOTHING, FAILURE);
	singleton()->img->addr = mlx_get_data_addr(singleton()->img->img_ptr,
		&singleton()->img->bpp,
		&singleton()->img->line_len,
		&singleton()->img->endian);
	singleton()->img->width = WIDTH;
	singleton()->img->height = HEIGTH;
}

static void	do_mlx(void)
{
	singleton()->mlx_ptr = mlx_init();
	if (!singleton()->mlx_ptr)
		__exit__(E_MALLOC, NULL, NOTHING, FAILURE);
	mlx_do_key_autorepeaton(singleton()->mlx_ptr);
	singleton()->win_ptr = mlx_new_window(singleton()->mlx_ptr,
		WIDTH,
		HEIGTH,
		"So_long");
	new_image();
	init_key();
	load_tex();
	mlx_hook(singleton()->win_ptr, 2, 1L << 0, event_key_press, singleton());
	mlx_hook(singleton()->win_ptr, 3, 1L << 1, event_key_release, singleton());
	mlx_hook(singleton()->win_ptr,
		RED_CROSS, 1L << 2, event_destroy_win, singleton());
	mlx_loop_hook(singleton()->mlx_ptr, event_loop, NULL);
	mlx_loop(singleton()->mlx_ptr);
}

int	main(int ac, char **av)
{
	check_ac(ac);
	parsing(av[1]);
	do_mlx();
	return (SUCCESS);
}
