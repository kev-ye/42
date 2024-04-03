/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:11:10 by kaye              #+#    #+#             */
/*   Updated: 2021/12/12 19:42:29 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

/*
 * defines
 */
/** @brief Verbose mode flag */
# ifndef VERBOSE
#  define VERBOSE 0
# endif

// this define can be delete
/** @brief Big prime number to avoid collisions, also size of array */
# ifndef HASH_MAX
// #  define HASH_MAX 193939
#  define HASH_MAX 1939390
# endif

/**	@brief Prime number roughly equal to the number of printable characters */
# ifndef HASH_PRIME
#  define HASH_PRIME 101
# endif

// this define can be delete
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# ifndef MALLOC_SIZE
#  define MALLOC_SIZE 2147483647
# endif

/** @brief boolean define */
# define BOOL unsigned int
# define TRUE 1
# define FALSE 0

/** @brief syscall error */
# define SYSCALL_ERROR -1

/*
 * includes
 */
# include <unistd.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>

#endif