/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdint.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:42:44 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 14:33:22 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDINT_H
# define FT_STDINT_H

# include <stdint.h>

# if !defined(__CLANG_STDINT_H)

typedef signed char				t_int8;
typedef short					t_int16;
typedef int						t_int32;
typedef long long int			t_int64;

typedef unsigned char			t_uint8;
typedef unsigned short			t_uint16;
typedef unsigned int			t_uint32;
typedef unsigned long long int	t_uint64;

# else

typedef int8_t					t_int8;
typedef int16_t					t_int16;
typedef int32_t					t_int32;
typedef int64_t					t_int64;

typedef uint8_t					t_uint8;
typedef uint16_t				t_uint16;
typedef uint32_t				t_uint32;
typedef uint64_t				t_uint64;

# endif

#endif
