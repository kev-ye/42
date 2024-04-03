/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:58:40 by kaye              #+#    #+#             */
/*   Updated: 2021/11/30 14:31:46 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

/** @brief anscii code */
# define S_NONE "\033[0m"
# define S_BLACK "\033[1;30m"
# define S_RED "\033[1;31m"
# define S_GREEN "\033[1;32m"
# define S_YELLOW "\033[1;33m"
# define S_BLUE "\033[1;34m"
# define S_PURPLE "\033[1;35m"
# define S_CYAN "\033[1;36m"

/** @brief debug */
// # define LOG printf("here: line: ["S_RED"%d"S_NONE"] file: ["S_RED"%s"S_NONE"]\n", __LINE__, __FILE__)
// # define DEBUGP(x) printf("address: ["S_RED"%p"S_NONE"] -> ", x);LOG;
// # define DEBUGS(s) printf("content: ["S_RED"%s"S_NONE"] -> ", s);LOG;

/** @brief boolean define */
# define BOOL unsigned int
# define TRUE 1
# define FALSE 0

/** @brief exit return define */
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

/** @brief return define */
# define SUCCESSE 0
# define FAILURE 1

/** @brief MLX INFO */
# define W_NAME "Cub3D"
# define W_HEIGHT 800
# define W_WIDTH 800

/** @brief syscall error */
# define SYSCALL_ERROR -1

/** @brief array */
# define PATHMAX 4
# define COLORMAX 3
# define TEXMAX 4
# define KEYMAX 6

/** @brief message */
# define USAGE "usage: ./cub3d [\033[1;33m[map].cub]\033[0m]\n"
# define E_SYS "SYSCALL failed\n"
# define E_PATH "PATH file no exist\n"
# define E_EMPTY "CONFIG is empty\n"
# define E_ID "ID error\n"
# define E_MAP "MAP: basic error\n"
# define E_SURROUND "MAP: no surround\n"
# define E_PLAYER "MAP: player != 1\n"
# define E_MLX "MLX: basic error\n"
# define E_IMG "MLX: load tex error\n"

/** @brief key code macos / linux */
# if defined (__APPLE__) && (__MACH__)
#  define K_ESC 53
#  define K_W 13
#  define K_S 1
#  define K_A 0
#  define K_D 2
#  define K_LEFT 123
#  define K_RIGHT 124
#  define RED_CROSS 17
# else
#  define K_ESC 65307
#  define K_W 119
#  define K_S 115
#  define K_A 97
#  define K_D 100
#  define K_LEFT 65361
#  define K_RIGHT 65363
#  define RED_CROSS 33
# endif

/** @brief includes */
# if defined(__linux__)
#  include <stdint.h>
# endif
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>
# include "libft.h"

#endif
