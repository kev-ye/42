/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyControl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:48:58 by kaye              #+#    #+#             */
/*   Updated: 2021/11/30 14:32:44 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_pressing(int keycode)
{
	const int	key[] = {K_W, K_S, K_A, K_D, K_LEFT, K_RIGHT};
	int			i;

	i = 0;
	if (keycode == K_ESC)
		exit_clean(NULL, __FILE__, __LINE__);
	else
	{
		while (i < KEYMAX)
		{
			if (keycode == key[i] && sglt()->key[i] == FALSE)
				sglt()->key[i] = TRUE;
			++i;
		}
	}
	return (1);
}

int	key_releasing(int keycode)
{
	const int	key[] = {K_W, K_S, K_A, K_D, K_LEFT, K_RIGHT};
	int			i;

	i = 0;
	if (keycode == K_ESC)
		exit_clean(NULL, __FILE__, __LINE__);
	else
	{
		while (i < KEYMAX)
		{
			if (keycode == key[i] && sglt()->key[i] == TRUE)
				sglt()->key[i] = FALSE;
			++i;
		}
	}
	return (1);
}

void	key_control(void)
{
	static void		(*func_ptr[KEYMAX])() = {
		move_w,
		move_s,
		move_a,
		move_d,
		rot_left,
		rot_right
	};
	t_cub3d const	*ptr = sglt();
	int				i;

	i = 0;
	while (i < KEYMAX)
	{
		if (TRUE == ptr->key[i])
			(*func_ptr[i])();
		++i;
	}
}
