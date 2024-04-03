/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 21:43:00 by kaye              #+#    #+#             */
/*   Updated: 2021/03/02 12:04:58 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		r_max(t_win *new_win, int *x, int *y)
{
	int x_max;
	int y_max;

	mlx_get_screen_size(new_win->mlx_ptr, &x_max, &y_max);
	if (*x > x_max)
		*x = x_max;
	if (*y > y_max)
		*y = y_max;
}

static t_win	*init_mlx_win(char *path, int save)
{
	t_win *new_win;

	if (!(new_win = malloc(sizeof(t_win))))
		return (NULL);
	ft_bzero(new_win, sizeof(t_win));
	if (!(new_win->desc_info = check_file(new_win, path)))
		return (NULL);
	if (!(new_win->mlx_ptr = mlx_init()))
		return (NULL);
	new_win->width = new_win->desc_info->r_x;
	new_win->height = new_win->desc_info->r_y;
	r_max(new_win, &new_win->width, &new_win->height);
	new_win->save = save;
	if (!new_win->save)
		if (!(new_win->win_ptr = mlx_new_window(new_win->mlx_ptr,
						new_win->width, new_win->height, "cub3D")))
			return (NULL);
	if (!(new_win->img = new_image(new_win, new_win->width, new_win->height)))
		return (NULL);
	return (new_win);
}

static int		check_ac(int ac)
{
	int save;

	if (ac < 2)
		msg_error(NULL, "Too few arguments\n");
	if (ac > 3)
		msg_error(NULL, "Too much arguments\n");
	save = 0;
	if (ac == 3)
		save = 1;
	return (save);
}

int				main(int ac, char **av)
{
	t_win	*win;
	int		save;

	save = check_ac(ac);
	if (!(win = init_mlx_win(av[1], save)) || !(init_key(win)) ||
			!(init_camera(win)) || !(init_tex(win)) || !(init_sprite(win)))
		msg_error(win, "Error : Malloc/mlx error\n");
	if (save)
	{
		if (ft_strcmp(av[2], "--save") != 0)
			msg_error(win, "The second argumnets isn't --save\n");
		make_bmp(win);
	}
	mlx_hook(win->win_ptr, 2, 1L << 0, event_key_press, win);
	mlx_hook(win->win_ptr, 3, 1L << 1, event_key_release, win);
	mlx_hook(win->win_ptr, RED_CROSS, 1L << 2, event_destroy_win, win);
	mlx_loop_hook(win->mlx_ptr, event_loop, win);
	mlx_loop(win->mlx_ptr);
	return (0);
}
