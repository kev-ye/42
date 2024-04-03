/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 16:50:09 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 20:58:34 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

/**
 * @brief anscii code
 */
# define ANSCII_CLEAR "\033[0m"
# define ANSCII_BLACK "\033[1;30m"
# define ANSCII_RED "\033[1;31m"
# define ANSCII_GREEN "\033[1;32m"
# define ANSCII_YELLOW "\033[1;33m"
# define ANSCII_BLUE "\033[1;34m"
# define ANSCII_PURPLE "\033[1;35m"
# define ANSCII_CYAN "\033[1;36m"

/**
 * @brief PUTNBR BUFFER SIZE
 */
# define BUFFER_SIZE_PN 11

/**
 * @brief boolean define
 */
# define BOOL unsigned int
# define TRUE 1
# define FALSE 0

/**
 * @brief TEST STATUS
 */
# define STATUS_SUCCESS 0
# define STATUS_FAILURE -1

/**
 * @brief syscall error
 */
# define SYSCALL_ERROR -1

/**
 * @brief STATUS
 */
# if defined(BONUS)
#  define STATUS_MAX 9
#  define SIG_MAX 7
# else
#  define STATUS_MAX 4
#  define SIG_MAX 2
# endif
# define STATUS_OK 1
# define STATUS_KO 2
# define STATUS_SIGSEGV 3
# define STATUS_SIGBUS 4
# define STATUS_SIGABRT 5
# define STATUS_SIGFPE 6
# define STATUS_SIGPIPE 7
# define STATUS_SIGILL 8
# define STATUS_TIMEOUT 9

/**
 * @brief includes
 */
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

# if defined(BONUS)
#  include <stdio.h>
# endif

#endif
