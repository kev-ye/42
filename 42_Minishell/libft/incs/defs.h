/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 21:09:44 by besellem          #+#    #+#             */
/*   Updated: 2021/05/10 00:35:18 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

/*
** When LIBC_NO_CRASH_ON_NULL is set to 1 (default), it is used to handle
** the cases where the libc actually segfault by passing a NULL ptr.
**
** When defined, we can use ft_strlen(NULL), ft_strdup(NULL),
** or ft_strchr(NULL, 42), for example, without segfault.
**
** However, if you want to crash where the libc is crashing, use the flag
** `-D LIBC_NO_CRASH_ON_NULL=0' at compile time.
*/
# if !defined(LIBC_NO_CRASH_ON_NULL)
#  define LIBC_NO_CRASH_ON_NULL 1
# else
#  define LIBC_NO_CRASH_ON_NULL 0
# endif

/*
** Useful macros to print out a message with a ft_printf or a write for example.
** Does not pass the norm unfortunately. Useful for debugging though.
**
** #define STRINGIFY(x) #x
** #define TOSTRING(x) STRINGIFY(x)
** #define PRINT_ERR(s)	printf("\e[1;31m" __FILE__ ":" TOSTRING(__LINE__) \
						":\e[0m " s "\n");
*/

#endif
