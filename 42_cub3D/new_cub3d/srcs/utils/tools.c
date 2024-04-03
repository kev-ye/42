/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:24:14 by kaye              #+#    #+#             */
/*   Updated: 2021/11/29 22:16:35 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub3d	*sglt(void)
{
	static t_cub3d	*sglt = NULL;

	if (NULL == sglt)
	{
		sglt = ft_calloc(1, sizeof(t_cub3d));
		if (NULL == sglt)
			exit_clean(E_SYS, __FILE__, __LINE__);
	}
	return (sglt);
}

uint32_t	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
