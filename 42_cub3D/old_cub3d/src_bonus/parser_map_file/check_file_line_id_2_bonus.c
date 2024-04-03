/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_line_id_2_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:14:27 by kaye              #+#    #+#             */
/*   Updated: 2021/02/09 09:57:50 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		check_file_line_info_done(t_desc desc)
{
	if (desc.r == 0 || desc.no == 0 || desc.so == 0 || desc.we == 0 ||
			desc.ea == 0 || desc.s == 0 || desc.f == 0 || desc.c == 0 ||
			desc.b == 0 || desc.l == 0 || desc.m == 0 || desc.g == 0)
		return (1);
	else if (desc.r == 1 && desc.no == 1 && desc.so == 1 && desc.we == 1 &&
			desc.ea == 1 && desc.s == 1 && desc.f == 1 && desc.c == 1 &&
			desc.b == 1 && desc.l == 1 && desc.m == 1 && desc.g == 1)
		return (1);
	return (0);
}
