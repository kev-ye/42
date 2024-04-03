/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdlib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 10:54:31 by besellem          #+#    #+#             */
/*   Updated: 2021/05/16 01:02:00 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDLIB_H
# define FT_STDLIB_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>

/*
** Memory
*/
void		*ft_calloc(size_t count, size_t size);

/*
** Number Conversions
*/
int			ft_atoi(const char *str);
int			ft_atoi_base(char *str, char *base);
long		ft_atol(const char *str);
long long	ft_atoll(const char *str);

double		ft_atod(const char *str);
long double	ft_atold(const char *str);

long		ft_strtol(const char *str, char **endptr, int base);
long long	ft_strtoll(const char *str, char **endptr, int base);

char		*ft_itoa(int n);
char		*ft_itoa_base(long long n, char *base);

int			ft_nblen(long long n);
int			ft_nblen_base(long long n, int base);

/*
** Random number generation
*/
long		ft_random(void);

#endif
