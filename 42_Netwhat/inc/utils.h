/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 17:01:36 by kaye              #+#    #+#             */
/*   Updated: 2020/12/06 21:44:32 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include <libc.h>

typedef struct s_ip
{
    int ip1;
    int ip2;
    int ip3;
    int ip4;
}              t_ip;


int     get_part_mask(int mask_ip_num);
long    get_ip_number(int mask1, int mask2, int mask3, int mask4);
void    calcul_ip_with_mask();
void    address_prive();
void    address_public();
void    calcul_mask();
int     get_cidr(int mask);
t_ip    get_range_ip(t_ip range_ip, long range);
t_ip    init_ip();
void    model_osi();

#endif