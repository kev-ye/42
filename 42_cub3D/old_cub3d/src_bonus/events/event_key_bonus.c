/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 19:04:13 by kaye              #+#    #+#             */
/*   Updated: 2021/02/08 12:00:54 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		event_key_press(int keycode, t_win *win)
{
	if (keycode == KEY_CODE_ESC)
		shut_down(win);
	else if (keycode == KEY_CODE_W && win->key_code->key_w == 0)
		win->key_code->key_w = 1;
	else if (keycode == KEY_CODE_S && win->key_code->key_s == 0)
		win->key_code->key_s = 1;
	else if (keycode == KEY_CODE_A && win->key_code->key_a == 0)
		win->key_code->key_a = 1;
	else if (keycode == KEY_CODE_D && win->key_code->key_d == 0)
		win->key_code->key_d = 1;
	else if (keycode == KEY_CODE_LEFT && win->key_code->key_left == 0)
		win->key_code->key_left = 1;
	else if (keycode == KEY_CODE_RIGHT && win->key_code->key_right == 0)
		win->key_code->key_right = 1;
	else if (keycode == KEY_CODE_UP && win->key_code->key_up == 0)
		win->key_code->key_up = 1;
	else if (keycode == KEY_CODE_DOWN && win->key_code->key_down == 0)
		win->key_code->key_down = 1;
	return (1);
}

int		event_key_release(int keycode, t_win *win)
{
	if (keycode == KEY_CODE_ESC)
		shut_down(win);
	else if (keycode == KEY_CODE_W && win->key_code->key_w == 1)
		win->key_code->key_w = 0;
	else if (keycode == KEY_CODE_S && win->key_code->key_s == 1)
		win->key_code->key_s = 0;
	else if (keycode == KEY_CODE_A && win->key_code->key_a == 1)
		win->key_code->key_a = 0;
	else if (keycode == KEY_CODE_D && win->key_code->key_d == 1)
		win->key_code->key_d = 0;
	else if (keycode == KEY_CODE_LEFT && win->key_code->key_left == 1)
		win->key_code->key_left = 0;
	else if (keycode == KEY_CODE_RIGHT && win->key_code->key_right == 1)
		win->key_code->key_right = 0;
	else if (keycode == KEY_CODE_UP && win->key_code->key_up == 1)
		win->key_code->key_up = 0;
	else if (keycode == KEY_CODE_DOWN && win->key_code->key_down == 1)
		win->key_code->key_down = 0;
	return (1);
}

int		event_key(t_win *win)
{
	if (win->key_code->key_w == 1)
		move_w(win);
	if (win->key_code->key_s == 1)
		move_s(win);
	if (win->key_code->key_a == 1)
		move_a(win);
	if (win->key_code->key_d == 1)
		move_d(win);
	if (win->key_code->key_left == 1)
		turn_left(win);
	if (win->key_code->key_right == 1)
		turn_right(win);
	if (win->key_code->key_up == 1)
		turn_up(win);
	if (win->key_code->key_down == 1)
		turn_down(win);
	return (1);
}

int		init_key(t_win *win)
{
	if (!(win->key_code = malloc(sizeof(t_key))))
		return (0);
	ft_bzero(win->key_code, sizeof(t_key));
	win->key_code->key_w = 0;
	win->key_code->key_s = 0;
	win->key_code->key_a = 0;
	win->key_code->key_d = 0;
	win->key_code->key_left = 0;
	win->key_code->key_right = 0;
	win->key_code->key_up = 0;
	win->key_code->key_down = 0;
	return (1);
}
