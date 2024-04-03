/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_range_ip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 20:20:29 by kaye              #+#    #+#             */
/*   Updated: 2020/12/06 20:49:16 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_ip    get_range_ip(t_ip range_ip, long range)
{
    while (range > 0)
    {
        while (range > 0)
        {
            while (range > 0)
            {
                while (range > 0)
                {
                    if (range <= 0)
                        return (range_ip);
                    while (range_ip.ip4 < 256)
                    {
                        ++range_ip.ip4;
                        --range;
                    }
                    if (range_ip.ip4 == 256)
                    {
                        range_ip.ip4 = 255;
                        break ;
                    }
                }
                if (range <= 0)
                    return (range_ip);
                if (range_ip.ip3 < 256)
                {
                    ++range_ip.ip3;
                    range_ip.ip4 = 0;
                }
                if (range_ip.ip3 == 256)
                {
                    range_ip.ip3 = 255;
                    break ;
                }
            }
            if (range <= 0)
                return (range_ip);
            if (range_ip.ip2 < 256)
            {
                ++range_ip.ip2;
                range_ip.ip3 = 0;
            }
            if (range_ip.ip2 == 256)
            {
                range_ip.ip2 = 255;
                break ;
            }
        }
        if (range <= 0)
            return (range_ip);
        if (range_ip.ip1 < 256)
        {
            ++range_ip.ip1;
            range_ip.ip2 = 0;
        }
        if (range_ip.ip1 == 256)
        {
            range_ip.ip1 = 255;
            break ;
        }
    }
    return (range_ip);
}