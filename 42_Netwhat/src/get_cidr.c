/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cidr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 23:42:16 by kaye              #+#    #+#             */
/*   Updated: 2020/12/05 23:59:07 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int get_cidr(int mask)
{
    int cidr;

    cidr = 0;
    if (mask == 255)
        cidr = 8;
    else if (mask == 254)
        cidr = 7;
    else if (mask == 253)
        cidr = 6;
    else if (mask == 248)
        cidr = 5;
    else if (mask == 240)
        cidr = 4;
    else if (mask == 224)
        cidr = 3;
    else if (mask == 192)
        cidr = 2;
    else if (mask == 128)
        cidr = 1;
    else if (mask == 0)
        cidr = 0;
    return (cidr);
}