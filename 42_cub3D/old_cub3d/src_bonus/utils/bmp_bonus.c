/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:40:36 by kaye              #+#    #+#             */
/*   Updated: 2021/03/01 19:45:58 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void		load_bar(long long current, long long max)
{
	long long bar_len;
	long long i;

	bar_len = 30;
	i = -1;
	ft_putstr(S_CLRLINE);
	while (++i < ((double)current / max) * bar_len)
		ft_putchar('|');
	while (i++ < bar_len)
		ft_putchar(' ');
	ft_putchar(' ');
	ft_putnbr_fd(((double)current / max) * 100, 1);
	ft_putchar('%');
	ft_putchar(' ');
}

static void		bmp_file_header(t_win *win, int fd)
{
	int size;
	int get_value;

	get_value = write(fd, "BM", 2);
	size = win->img->bpp * win->img->width * win->img->height + 54 * 8;
	printf("Loading "S_CYAN"%s"S_NONE" ...\n", "save.bmp");
	get_value = write(fd, &size, 4);
	size = 0;
	get_value = write(fd, &size, 2);
	get_value = write(fd, &size, 2);
	size = 54;
	get_value = write(fd, &size, 4);
	(void)get_value;
}

static void		bmp_infomation(t_win *win, int fd)
{
	int size;
	int get_value;

	size = 40;
	get_value = write(fd, &size, 4);
	get_value = write(fd, &win->img->width, 4);
	get_value = write(fd, &win->img->height, 4);
	size = 1;
	get_value = write(fd, &size, 2);
	get_value = write(fd, &win->img->bpp, 2);
	size = 0;
	get_value = write(fd, &size, 4);
	get_value = write(fd, &size, 4);
	get_value = write(fd, &size, 4);
	get_value = write(fd, &size, 4);
	get_value = write(fd, &size, 4);
	get_value = write(fd, &size, 4);
	(void)get_value;
}

static void		bmp_data(t_win *win, int fd)
{
	char	*ptr;
	int		x;
	int		y;
	int		get_value;

	y = win->img->height;
	while (y--)
	{
		x = -1;
		while (++x < win->img->width)
		{
			ptr = win->img->addr
					+ (y * win->img->line_len + x * (win->img->bpp / 8));
			get_value = write(fd, &(*(int *)ptr), 4);
		}
		load_bar(win->img->height - y, win->img->height);
	}
	(void)get_value;
}

void			make_bmp(t_win *win)
{
	int fd;

	ray_casting(win);
	if ((fd = open("./save.bmp", O_WRONLY | O_CREAT, 0755)) == -1)
		msg_error(win, "Malloc in mode --save\n");
	bmp_file_header(win, fd);
	load_bar(0, win->img->height);
	bmp_infomation(win, fd);
	bmp_data(win, fd);
	close(fd);
	free_win(win);
	printf("-> "S_CYAN"DONE !\n"S_NONE);
	exit(0);
}
