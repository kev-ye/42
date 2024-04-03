/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_part_mask.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 17:02:17 by kaye              #+#    #+#             */
/*   Updated: 2020/12/06 20:54:07 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int get_part_mask(int mask_ip_num)
{
    int part_mask;

    part_mask = 0;
    if (mask_ip_num == 8)
        part_mask = 255;
    else if (mask_ip_num == 7)
        part_mask = 254;
    else if (mask_ip_num == 6)
        part_mask = 252;
    else if (mask_ip_num == 5)
        part_mask = 248;
    else if (mask_ip_num == 4)
        part_mask = 240;
    else if (mask_ip_num == 3)
        part_mask = 224;
    else if (mask_ip_num == 2)
            part_mask = 192;
    else if (mask_ip_num == 1)
        part_mask = 128;
    else if (mask_ip_num == 0)
        part_mask = 0;
    return (part_mask);
}