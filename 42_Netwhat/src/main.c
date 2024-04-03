/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 17:40:20 by kaye              #+#    #+#             */
/*   Updated: 2020/12/07 02:01:12 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int main()
{
    int choose;
    char re[1];
menu:
    choose = 0;
    system("clear");
    printf("\n");
    printf("\033[1;32m====================== CHOOSE WHAT ARE YOU WANT ======================\n\033[0m");
    printf("\n");
    printf("-------------------------> 1. Private IP. <---------------------------\n");
    printf("-------------------------> 2. Public IP. <----------------------------\n");
    printf("-------------------------> 3. Model OSI. <----------------------------\n");
    printf("-------------------------> 4. Calcul IP/MASK IP. <--------------------\n");
    printf("-------------------------> 5. Calcul MASK IP. <-----------------------\n");
    printf("-------------------------> 0. QUIT SYSTEM. <--------------------------\n");
    printf("\n");
    printf("\033[1;32m======================================================================\n\033[0m");
    printf("\n");
    printf("-------------------------> Enter choose : ");
    scanf("%d", &choose);
    getchar();
    system("clear");
    if (choose == 1)
    {
        printf("\033[1;32m======================================================================\n\033[0m");
        printf("\n");
        printf("-------------------------> 1. Private IP. <---------------------------\n");
        printf("\n");
        address_prive();
        printf("\n");
        printf("---> Press enter to continu ...");
        getchar();
        system("clear");
        goto menu;
    }
    else if (choose == 2)
    {
        printf("\033[1;32m======================================================================\n\033[0m");
        printf("\n");
        printf("-------------------------> 1. Public IP. <----------------------------\n");
        printf("\n");
        address_public();
        printf("\n");
        printf("---> Press enter to continu ...");
        getchar();
        system("clear");
        goto menu;
    }
    else if (choose == 3)
    {
        printf("\033[1;32m======================================================================\n\033[0m");
        printf("\n");
        printf("-------------------------> 3. Model OSI. <---------------------------\n");
        printf("\n");
        model_osi();
        printf("\n");
        printf("---> Press enter to continu ...");
        getchar();
        system("clear");
        goto menu;
    }
    else if (choose == 4)
    {
        calcul_ip_with_mask();
        printf("\n");
        system("clear");
        goto menu;
    }
    else if (choose == 5)
    {
        calcul_mask();
        printf("\n");
        system("clear");
        goto menu;
    }
    else if (choose == 0)
    {
        system("clear");
        exit(0);
    }
    return (0);
}